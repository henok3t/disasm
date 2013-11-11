#include "SourceCode.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <fstream>

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

vector<int> getBinary(int d)
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

string getAddress(char c)
{        
        
}

SourceCode::SourceCode(SymTable ST)
{
        this->tables = ST;
}

string getReG(char c)
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

vector<Instruction> SourceCode::getInstructions(string objFile)
{
        int i, j, d, format, insCount, recordSize; 
        std::string line, R1, R2;
        vector<int> binary_opcode;
        char newByte[2], Operand[100],;
        
        vector<Instruction> Insts;
        
        ifstream obj(objFile.c_str());
        
        insCount  = 0;
        
        if(obj.is_open())
        {
                 while ( getline (obj,line) )
                 {
                         switch(line.at(0))
                         {
                                 case 'H':
                                        break;
                                 case 'D':
                                        break;
                                 case 'R':
                                        break;                                        
                                 case 'T':
                                   // Calculate the length of object code in this record in decimal.
                                   //(col 8-9)
                                       // recordSize = 16*(hex_To_int(line.at(7))) + hex_To_int(line.at(8));
                                          
                                           recordSize = line.lenght() - 9;
                                                
                                                i=9;
                                        
                                        while(recordSize > 0)
                                        {        
                                                 d = hex_To_int(line.at(i+1));
                                                 
                                                //find the binary representation of the second half byte of the opcode
                                                binary_opcode = getBinary(d);
                                                
                                                // fint the real opcode, by geting rid of the last 2 bits
                                                
                                                newByte[1] = int_To_hex((8*binary_opcode[0]) + 4*binary_opcode[1]);
                                                newByte[0] = line.at(i);
                                                
                                                // look i up in the map                 
                                                Instruction  ins(string(newByte), this->tables);
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
                                                                 R1 = getReg(line.at(i+2));
                                                                 R2 = getReg(line.at(i+3));                
                                                                 
                                                if(R1.lenght()=2)
                                                     {
                                                     	operand[0] = R1.at(0);
                                                     	operand[1] = R1.at(1);
                                                    	operand[2] = ',';
                                                    	 
                                                    	 if(R2.lenght()=2)
                                                    		{
                                                    			operand[3] = R2.at(0);
                                                    		 	operand[4] = R2.at(1);
                                                    			operand[5] = '\n';
                                                    			ins.SetOperand(std::string(Operand));
                                                    		}
                                                    		else
                                                    		{
                                                    			operand[3] = R2.at(0);
                                                    			operand[4] = '\n';
                                                    			ins.SetOperand(std::string(Operand));
                                                    		}
                                                     }
                                                     else
                                                     {
                                                     	operand[0]= R1.at(0);
                                                     	operand[1] = ',';
                                                     	
                                                     	if(R2.lenght()=2)
                                                    		{
                                                    			operand[2] = R2.at(0);
                                                    		 	operand[3] = R2.at(1);
                                                    			operand[4] = '\n';
                                                    			ins.SetOperand(std::string(Operand));
                                                    		}
                                                    		else
                                                    		{
                                                    			operand[2] = R2.at(0);
                                                    			operand[3] = '\n';
                                                    			ins.SetOperand(std::string(Operand));
                                                    		}
                                                     	
                                                     }
                                                      recordSize -= 4;
                                                      i += 4s; 
                                                      
                                                      break;          	
                                                        case 3:
                                                                break;
                                                        case 4:
                                                                break;
                                                }      
                                                Insts[insCount++] = ins;
                                                
                                                              
                                        }
                                        break;
                                 case 'M':
                                        break;
                                 case 'E':
                                        break;
                         }
                 }
        }
        obj.close();
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
