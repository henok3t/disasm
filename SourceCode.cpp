/* Information about Assignment
	Name: Henok Tadesse
	UserAccount: masc0753
	Partner Name: Joseph Mouawad
	Partner UserAccount: masc0736
	class: cs530
	Assignment: Program Assignment 2
 */
 

#include "SourceCode.hpp"
#include "Instruction.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <fstream>
#include "LineCode.hpp"
#include <string.h>
#include <sstream>

using namespace std;

SourceCode::SourceCode(Table ST, string sourcefile, string output):
	source(sourcefile.c_str()),
	outfile(output.c_str())
{
        this->tables = ST;
}

void SourceCode::createInstructions()
{
	string line;   	 
	char locationCounter[5] = "0000";    
	char location[5];
	if(source.is_open())
	{
		 while ( getline (source,line) )
		 {
			 switch(line.at(0))
			 {
				 case 'H':
						handleHeaderRecord(line);
						break;                                      
				 case 'T':
						memcpy(location, &line[3], 4);
						location[4] = '\0';
						checkLocationDifference(locationCounter, location);						
						handleTextRecord(line, (char*)locationCounter);
						break;
				 case 'M':								
						// nothing to do for modification record
						break;
				 case 'E':
						checkLocationDifference(locationCounter, programSize.c_str());	
						handleEndRecord(line);
						break;
			 }
		 }
	}
}

void SourceCode::handleHeaderRecord(string& line)
{
	cout<<"Got Header Record"<<endl;
	char lab[7];
	char operand[8] = {'0'};
	operand[0] = ' '; // nixbpe doesn't apply here
	char length[5] = "0000";
	
	// get label
	for(int i=0; i < 6; i++)
	{
		if( line[i+1] == ' ')
		{
			lab[i] = '\0';
			break;
		}
		lab[i] = line[i+1];
	}
	lab[6] = '\0';
	
	// get start address
	bool startReading = false; int j = 1;	
	for(int i = 1; i < 7; i++ )
	{
		if(line[i+7] != '0')
			startReading = true;		
		if(startReading)
		{
			operand[j] = line[i+7];
			j++;
		}
	}
	if( j == 1 ) // address is zero
	{
		operand[j] = '0';
		j++;
	}
	operand[j] = '\0';
	
	// get Length
	for(int i = 0; i < 4; i++)
		length[i] = line[i+15];
	programSize = string(length);
	cout<<"Program Size: "<<programSize<<endl;
	
	code.push_back(LineCode(string(lab), "START", string(operand)));		
	cout<<"Processed Header Record"<<endl;
}
		
void SourceCode::handleTextRecord(string& line, char* locationCounter)
{
	cout<<"Got Text Record"<<endl;
	map<string, string> literals;
	int position,  decimal, format, insCount, recordSize, opos; 
	int n = 0, i = 0, x = 0, b = 0, p = 0, e = 0; // nixbpe
	std::string R1, R2; // register for format to instructions
	vector<int> binary_opcode;
	char newByte[3], operand[100], name[12], disp[5];
	char BaseReg[5] = "0000";
	bool basemode = false;
	disp[4] = '\0';

	// Calculate the length of object code in this record in decimal.
	//(col 8-9)
	recordSize = (16*(hex_To_int(line.at(7))) + hex_To_int(line.at(8)))*2;                                              
	position=9; // starting point of the instructions in the text record                                       
	while(recordSize > 0)
	{   
		// check if locationcounter is in literal table
		if(literals.count(string(locationCounter)) == 1)
		{
			code.push_back(LineCode("", "LTORG", ""));
			map<string, string>::iterator iter;
			for(iter = literals.begin(); iter != literals.end(); ++iter)
			{
				for(int l = 3; l < (iter->second.size() - 1); l++)
				{
					addHex(locationCounter, "0001", locationCounter);
					recordSize -= 1;
					position += 1;
					if(iter->second[1] == 'X') // count by 2 if hexadeximal
					{
						l++;
						recordSize -= 1;
						position += 1;
					}
				}
			}
			literals.clear();
			continue;
		}
		
		//find the binary representation of the second half byte of the opcode
		decimal = hex_To_int(line.at(position+1));	 
		getBinary(decimal, binary_opcode);
		// find the real opcode, by geting rid of the last 2 bits
		newByte[1] = int_To_hex( 8*binary_opcode[0] + 4*binary_opcode[1] );
		newByte[0] = line[position];
		newByte[2] = '\0';

		n = binary_opcode[2];
		i = binary_opcode[3];

		// look it up in the map                 
		Instruction  ins(string(newByte), this->tables);
		format = ins.GetFormat(); 
		LineCode codeline;
		
		string posSymbol = tables.getSymbol(string(locationCounter));
		codeline.setLabel(posSymbol);
		
		if(format == 3)
		{
			decimal = hex_To_int(line.at(position+2));	
			getBinary(decimal, binary_opcode);
			x = binary_opcode[0];
			b = binary_opcode[1];
			p = binary_opcode[2];
			e = binary_opcode[3];			   
			
			if(e == 1)  // extended format 
			{
				ins.SetFormat(4);
				format = ins.GetFormat();				
				codeline.isExtended = true;	
							
			}				
		}	
		
		string instName = ins.GetName();
		int l;
		for(l = 0; l < instName.size(); l++)
		{
			name[l] = instName[l];
		}
		name[l] = '\0';
		
		codeline.setInstruction(name);
		
		switch(format)
		{
			case 1:
				operand[0] = '\0';
				addHex(locationCounter, "0001", locationCounter);
				codeline.setOperand(string(operand));	
				break;
			case 2:
				addHex(locationCounter, "0002", locationCounter);
				R1 = getReg(line.at(position+2));
				R2 = getReg(line.at(position+3));                
				operand[0] = R1.at(0);
				operand[1] = (R1.size() == 2) ? R1[1] : ',';
				operand[2] = (R1.size() == 2) ? ',' : R2[0];
				if(R2.size() == 2)
				{
					operand[3] = (R1.size() == 2) ? R2[0] : R2[1];
					operand[4] = (R1.size() == 2) ? R2[1] : '\0';
				}
				else
				{					
					operand[3] = (R1.size() == 2) ? R2[0] : '\0';
					operand[4] = '\0';
				}
				codeline.setOperand(" " + string(operand));				
				break;   						
			case 3:		
				addHex(locationCounter, "0003", locationCounter);	
				opos = 0;		
				if(i == 1 && n == 0) // immediate (operand = TA)
				{					
					operand[opos] = '#';
					opos++;
				}
				else if(i == 0 && n == 1) // Indirect (operand = [[TA]])
				{
					operand[opos] = '@';
					opos++;
				}
				
				// get the displacement
				for(int l = 0; l < 3; l++)
						disp[l+1] = line[position + 3 + l];
				disp[0] = (disp[1] == 'F') ? 'F' : '0';		
				
				if(b == 0 && p == 1) // PC-relative
				{								
					addHex(locationCounter, string(disp), disp);							
					string symbol = tables.getSymbol(string(disp));
					if(symbol[0] == '=')
						literals[string(disp)] = symbol;
					else
					{
						operand[opos] = ' ';
						opos++;
					}

					int l;
					for(l = 0; l < symbol.size(); l++)					
						operand[l + opos] = symbol[l];
					if( x == 1 )
					{
						operand[l + opos] = ',';
						operand[l + opos + 1] = 'X';
						l+=2;
					}
					operand[l + opos] = '\0';
				}
				else if(b == 1 && p == 0) // Base Relative
				{
					if(basemode == false)
					{
					   basemode = true;
					   code.push_back(LineCode("", "BASE", " " + tables.getSymbol(BaseReg)));					   
					}
					addHex(BaseReg, string(disp), disp);
					string symbol = tables.getSymbol(string(disp));
					if(symbol[0] == '=')
						literals[string(disp)] = symbol;
					else
					{
						operand[opos] = ' ';
						opos++;
					}
					int l;
					for(l = 0; l < symbol.size(); l++)					
						operand[l + opos] = symbol[l];
					if( x == 1 )
					{
						operand[l + opos] = ',';
						operand[l + opos + 1] = 'X';
						l+=2;
					}
					operand[l + opos] = '\0';
				}
				else
				{
					if(i == 1 && n == 0)
					{
						bool startReading = false; int j = opos;	
						for(int l = 0; l < 3; l++ )
						{
							if(line[position + 3 + l] != '0')
								startReading = true;		
							if(startReading)
							{
								operand[j] = line[position + 3 + l];
								j++;
							}
						}
						if( j == opos ) // address is zero
						{
							operand[j] = '0';
							j++;
						}
						operand[j] = '\0';					
					}
					else
					{
						string symbol = tables.getSymbol(string(disp));
						if(symbol[0] == '=')
							literals[string(disp)] = symbol;							
						else
						{
							operand[opos] = ' ';
							opos++;
						}
						int l;
						for(l = 0; l < symbol.size(); l++)					
							operand[l + opos] = symbol[l];
						if( x == 1 )
						{
							operand[l + opos] = ',';
							operand[l + opos + 1] = 'X';
							l+=2;
						}
						operand[l + opos] = '\0';
						if(codeline.getInstruction() == "RSUB") // RSUB is a wierd instruction
							operand[0] = '\0'; // No operand for RSUB
					}
				}				
					
				codeline.setOperand(string(operand));			
				break;
			case 4:
				addHex(locationCounter, "0004", locationCounter);				
				opos = 0;		
				if(i == 1 && n == 0) // immediate (operand = TA)
				{					
					operand[opos] = '#';
					opos++;
				}
				else if(i == 0 && n == 1) // Indirect (operand = [[TA]])
				{
					operand[opos] = '@';
					opos++;
				}
				
				// get the displacement
				for(int l = 0; l < 4; l++)
						disp[l] = line[position + 4 + l];	
				string symbol = tables.getSymbol(string(disp));
				if(symbol[0] == '=')
					literals[string(disp)] = symbol;
				else if( (i == 0 && n == 0) || (i == 1 && n == 1) )
				{
					operand[opos] = ' ';
					opos++;
				}
				int l;
				for(l = 0; l < symbol.size(); l++)					
					operand[l + opos] = symbol[l];
				if( x == 1 )
				{
					operand[l + opos] = ',';
					operand[l + opos + 1] = 'X';
					l+=2;
				}
				operand[l + opos] = '\0';			
				codeline.setOperand(string(operand));
				break;
		}     		
		recordSize-=format*2;
		position+=format*2;		
		if(codeline.getInstruction() == "LDB")	
		{			
			strcpy(BaseReg, disp);
		}
		code.push_back(codeline);
	}
	cout<<"Processed Text Record"<<endl;	
}

void SourceCode::handleEndRecord(string& line)
{
	cout<<"Got End Record"<<endl;
	char address[5];
	
	for(int i=0; i < 5; i++)
	{
		address[i] = line[i+3];
	}
	address[5] = '\0';
	string operand = tables.getSymbol(string(address));
	
	code.push_back(LineCode("", "END", " " + string(operand)));
	cout<<"Processed End Record"<<endl;
}               
                
void SourceCode::writeInstructions()
{
    cout<<"Writing to file"<<endl;
    
    for(int i = 0; i < code.size(); i++)
    {
		string label = code[i].getLabel();
		outfile<<label;
		for(int j = 0; j < (9 - label.size()); j++)
			outfile<<" ";
		if( code[i].isExtended )
			outfile<<"+";
		else
			outfile<<" ";
		string insts = code[i].getInstruction();
		outfile<<insts;
		for(int j = 0; j < (11 - insts.size()); j++)
			outfile<<" ";
		string op = code[i].getOperand();
		outfile<<op<<endl;
	}  
	cout<<"Finished Writing to file"<<endl;                 
}

int SourceCode::hex_To_int(char c)
{
        if(c <= 57 && c >= 48)             // 0-9
                        return int(c - 48);
                        
        else if(c <= 70 && c >= 65)        // A-F
                        return int(c - 65 + 10);
                                
        else if(c <= 102 && c >= 97)       //a-f   
                        return int(c - 97 + 10);

}

char SourceCode::int_To_hex(int i)
{
	if(i <= 9 && i >= 0)
			return char(i+48);
	else
	{
		switch(i)
		{
				case 10:
						return 'A';
						break;
				case 11:
						return 'B';
						break;
				case 12:
						return 'C';
						break;
				case 13:
						return 'D';
						break;
				case 14:
						return 'E';
						break;
				case 15:
						return 'F';
						break;                                        
		}
	}
	return '\0';
}

void SourceCode::getBinary(int d, vector<int>& binary_opcode)
{
	int j= 3;
	for(int i = binary_opcode.size(); i < 4; i++)
		binary_opcode.push_back(0);
	do
	{
		binary_opcode[j] = d%2; 
		d /=2;
		j--;
	}while(d>0);
					
	while(j>=0)
	{
			binary_opcode[j] = 0; 
			j--;
	}			 
}

string SourceCode::getReg(char c)
{
	switch(c)
	{
		case '0':
			return "A";
			break;
		case '1':
			return "X";
			break;
		case '2':
			return "L";
			break;
		case '3':
			return "B";
			break;
		case '4':
			return "S";
			break;
		case '5':
			return "T";
			break;
		case '6':
			return "F";
			break;
		case '8':
			return "PC";
			break;
		case '9':
			return "SW";
			break;
	}
}

void SourceCode::addHex(char* a, string b, char* sum)
{
	int carry = 0;
	for(int i = 3; i >=0; i--)
	{
		int tmpcarry = (hex_To_int(a[i]) + hex_To_int(b[i]) + carry)/16;
		sum[i] = int_To_hex( (hex_To_int(a[i]) + hex_To_int(b[i]) + carry)%16);	
		carry = tmpcarry;
	}
}


int SourceCode::hex_to_int(string hex)
{
	return 4096*(hex_To_int(hex[0])) + 256*(hex_To_int(hex[1])) + 16*(hex_To_int(hex[2])) + (hex_To_int(hex[3]));
}

void SourceCode::checkLocationDifference(char* start, const char* end)
{
	int current, next, last;
	map<string, string> symTab = tables.getSymTab();
	map<string, string>::iterator iter, nextIter;
	
	while(string(start) < end)
	{						
		for(iter = symTab.begin(); iter != symTab.end(); ++iter)
		{								
			if(iter->first == string(start))
			{									
				nextIter = ++iter; iter--;
				current = hex_to_int((iter)->first);
				if( (nextIter) != symTab.end() )
					next = hex_to_int((nextIter)->first);
				last = hex_to_int(string(end));
				int op = 0;
				if( next < last && (nextIter) != symTab.end())
					op = next - current;
				else
					op = last - current;
				ostringstream convert;
				if( op % 3 == 0 )
				{
					convert<<op/3;
					code.push_back(LineCode(iter->second, "RESW", " " + convert.str()));
				}
				else
				{
					convert<<op;									
					code.push_back(LineCode(iter->second, "RESB", " " + convert.str()));
				}
				for(int l = 0; l < op; l++) // Add op to location counter
					addHex(start, "0001", start);
			}
		}
	}
}
