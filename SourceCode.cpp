#include "SourceCode.hpp"
#include "Instruction.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <fstream>
#include "LineCode.hpp"

using namespace std;

SourceCode::SourceCode(SymTable ST, string sourcefile, string output):
	source(sourcefile.c_str()),
	outfile(output.c_str())
{
        this->tables = ST;
}

void SourceCode::createInstructions()
{
	string line;   	     
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
						handleTextRecord(line);
						break;
				 case 'M':
						handleModificationRecord(line);
						break;
				 case 'E':
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
	code.push_back(LineCode(string(lab), "START", string(operand)));		
	cout<<"Processed Header Record"<<endl;
}
		
void SourceCode::handleTextRecord(string& line)
{
	cout<<"Got Text Record"<<endl;
	vector<string> literals;
	int position,  decimal, format, insCount, recordSize; 
	int n = 0, i = 0, x = 0, b = 0, p = 0, e = 0; // nixbpe
	std::string R1, R2; // register for format to instructions
	vector<int> binary_opcode;
	char newByte[3], operand[100], name[12], disp[4];

	// Calculate the length of object code in this record in decimal.
	//(col 8-9)
	// recordSize = 16*(hex_To_int(line.at(7))) + hex_To_int(line.at(8));                                          
	recordSize = 12;                                                
	position=9; // starting point of the instructions in the text record                                       
	while(recordSize > 0)
	{   
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
		cout<<ins.GetName()<<endl;
		
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
				
				name[0] = '+';				

				string instName = ins.GetName();
				for(int l = 0; l < instName.size(); l++)
				{
					name[l+1] = instName[l];
				}
			}				
		}
		
		if( e != 1)
		{			
			string instName = ins.GetName();
			for(int l = 0; l < instName.size(); l++)
			{
				name[l] = instName[l];
			}
		}
		
		switch(format)
		{
			case 1:
				operand[0] = '\0';
				break;
			case 2:
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
				
				recordSize -= 4;
				break;   						
			case 3:					
				if(i == 1 && n == 0) // immediate (operand = TA)
				{					
					operand[0] = '#';
					
					if((b == 0 && p == 0) || (b == 1 && p == 1)) // Direct
					{
						// TA=disp (format 3) or address (format 4)                                                        		
					}
					else if(b == 0 && p == 1) // PC-relative
					{
						// TA=(PC)+disp						
					}
					else if(b == 1 && p == 0) // Base Relative
					{
					   //	TA=(B)+disp
					}
					ins.SetOperand(std::string(operand));
				}
				else if(i == 0 && n == 1) // Indirect (operand = [[TA]])
				{
					operand[0] = '@';
					
					if(b == 0 && p == 1) // PC-relative
					{
						// TA=(PC)+disp
						
					}
					else if(b == 1 && p == 0) // Base Relative
					{
					   //	TA=(B)+disp
					}
					ins.SetOperand(std::string(operand));
				}
				else if((i == 0 && n == 0) || (i == 1 && n == 1)) // Simple
				{
				
					if(x == 0)
					{
						// indexed
					}
					if((b == 0 && p == 0) || (b == 1 && p == 1)) // Direct
					{
						// TA=disp (format 3) or address (format 4)                                                        		
					}
					else if(b == 0 && p == 1) // PC-relative
					{
						// TA=(PC)+disp
						
					}
					else if(b == 1 && p == 0) // Base Relative
					{
					   //	TA=(B)+disp
					}
					ins.SetOperand(std::string(operand));
				}
				break;
			case 4:
				break;
		}     		
		recordSize-=format*2;		
		position+=format*2;		
	}
	cout<<"Processed Text Record"<<endl;	
}

void SourceCode::handleModificationRecord(string& line)
{
	cout<<"Got Modification Record"<<endl;
	cout<<"Processed Modification Record"<<endl;
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
		for(int j = 0; j < (10 - label.size()); j++)
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
                        
        else if(c <= 65 && c >= 70)        // A-F
                        return int(c - 65 + 10);
                                
        else if(c <= 97 && c >= 102)       //a-f   
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
