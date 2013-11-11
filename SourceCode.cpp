#include "SourceCode.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <fstream>
#include <math>

using namespace std;




int hex_To_int(char c)
{
	if(c <= 57 && c >= 48)             // 0-9
			return int(c - 48);
			
	else if(c <= 65 && c >= 70)        // A-F
			return int(c - 65 + 10);
				
	else if(c <= 97 && c >= 102)       //a-f   
			return int(c - 97 + 10);

}

char int_To_hex(int i)
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

int[] getBinary(int d)
{
 		int j= 3;
		int binary_opcode[4];
		
				 
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

string getAddress(char c)
{	
	
}


SourceCode::SourceCode(SymTable ST)
{
	this->tables = ST;
}

vector<Instruction> SourceCode::getInstructions(string objFile)
{
	int i,d, format; 
	std::string line, addR1, addR2, R1, R2;
	int binary_opcode[4];
	char newByte[2];
	
	vector<Instruction> Insts;
	
	ifstream obj(objFile);
	
	if(obj.is_open())
	{
		 while ( getline (obj,line) )
		 {
		 	switch(line.at(0))
		 	{
		 		case 'H':
		 		case 'D':
		 		case 'R':
		 		case 'T':
		 			{
		 		   // Calculate the length of object code in this record in decimal.
		 		   //(col 8-9)
		 		recordSize = 16*(hex_To_int(line.at(7))) + hex_To_int(line.at(8));
		 			
		 			i=9;
		 		
		 		while(i + 1 <= 68)
		 		{	
		 			 d = hex_To_int(line.at(i+1));
		 			 
		 	//find the binary representation of the second half byte of the opcode
		 			binary_opcode = getBinary(d);
		 			
		 		// fint the real opcode, by geting rid of the last 2 bits
		 		
		 		newByte[1] = char(int_To_hex((8*binary_opcode[0]) + 4*binary_opcode[1]);
		 		newByte[0] = line.at(i);
		 		
				// look i up in the map 		
		 		Instruction  ins = new Instruction(string(newByte), this->tables);
		 		ins.GetName();
		 		format = ins.GetFormat(); 
		 		
		 			if(format == 3)
		 				{
		 					binary_opcode = getBinary(line.at(i+2));
		 					
		 					if(binary_opcode[3] == 1)
		 						{
		 							ins.SetFormat(4);
		 							format = ins.GetFormat();
		 						}
		 							
		 					else
		 						ins.SetFormat(3);
		 						
		 					
		 				}
		 	
		 	
		 		switch(format)
		 		{
		 			case 1:
		 				break;
		 			case 2:
		 				 addR1 = getAddress(line.at(i+2));
		 				 addR2 = getAddress(line.at(i+3));
		 				 
		 				 R1= this.tables.getSymbol(addR1);
		 				 R2= this.tables.getSymbol(addR2);
		 	   
		 				 
		 				
		 			case 3:
		 			case 4:
		 		}

		 	
		 		
		 		}
		 				
		 			}
		 		case 'M':	
		 		case 'E':
		 	}
		 }
	}
	objCOde.close();
}

bool SourceCode::generateSourceCode(vector<Instruction>& vec)
{
	
}
		
		
bool SourceCode::loadToFile(string sourceFile)
{
			
}
		
		
void SourceCode::printSourceCode()
{
			
}