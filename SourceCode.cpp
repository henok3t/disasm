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
							 case 'D':
									handleDefineRecord(line);
									break;
							 case 'R':
									handleReferRecord(line);
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

void SourceCode::handleDefineRecord(string& line)
{
	cout<<"Got Define Record"<<endl;
	cout<<"Processed Define Record"<<endl;
}

void SourceCode::handleReferRecord(string& line)
{
	cout<<"Got Refer Record"<<endl;
	cout<<"Processed Refer Record"<<endl;
}
		
void SourceCode::handleTextRecord(string& line)
{
	cout<<"Got Text Record"<<endl;	
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
                return char(i);
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
}

vector<int> SourceCode::getBinary(int d)
{
                 int j= 3;
                vector<int> binary_opcode;                                 
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
                         
                         
                 return binary_opcode;
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
