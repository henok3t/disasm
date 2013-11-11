#include "symtable.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <fstream>
#include "Instruction.hpp"

using namespace std;


Instruction::Instruction(string key, SymTable Stable)
{
	this->opKey = key;
	this->Stable = Stable;
}

string Instruction::GetName()
{

}
	
int Instruction::GetFormat()
{
/*..........  not complete............*/
	//if(format == 3)
	//{
		//binary_opcode = getBinary(line.at(i+2));
		 					
		//if(binary_opcode[3] == 1)
		//ins.SetFormat(4);
		//else
		//ins.SetFormat(3);
	//}
		 		
}
	
int Instruction::GetLength()
{
	
}
	
void Instruction::SetOperand(char* op)
{

}

void Instruction::SetFormat(int)
{
	
}

