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
	
	struct opVals vals = Stable.getOpVal(key);
	
	this->format = vals.format;
	this->name = vals.name;
}

string Instruction::GetName()
{
	return name;
}
	
int Instruction::GetFormat()
{
	return format;		 		
}
	
int Instruction::GetLength()
{
	return format;	
}
	    
void Instruction::SetOperand(string op)
{
	this->operand = op;
}

void Instruction::SetFormat(int fmt)
{
	this->format = fmt;
	
}

