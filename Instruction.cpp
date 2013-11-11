#include "symtable.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <fstream>

using namespace std;


Instruciton::Instruction(stirng key, SymTable Stable)
{
	this.opKey = key;
	this.Stable = Stable;
}

string Instruciton::GetName()
{

}
	
string GetFormat()
{

/*..........  not complete............*/
	if(format == 3)
	{
		binary_opcode = getBinary(line.at(i+2));
		 					
		 if(binary_opcode[3] == 1)
		  	ins.SetFormat(4);
		 else
			ins.SetFormat(3);
	}
		 		
}
	
int GetLenght()
{
	
}
	
void SetOperand(char[] op)
{

}