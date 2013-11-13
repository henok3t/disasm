/* Information about Assignment
	Name: Henok Tadesse
	UserAccount: masc0753
	Partner Name: Joseph Mouawad
	Partner UserAccount: masc0736
	class: cs530
	Assignment: Program Assignment 2
 */

#include "symtable.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <fstream>
#include "Instruction.hpp"

using namespace std;

		// constructor 
Instruction::Instruction(string key, SymTable Stable)
{
	this->opKey = key;
	this->Stable = Stable;
	
	struct opVals vals = Stable.getOpVal(key);
	
	this->format = vals.format;
	this->name = vals.name;
}
                   // returns the Mneumonic of the instruciton
string Instruction::GetName()
{
	return name;
}
		// returns the format of the instruction (format 1,2, 3, or 4)
int Instruction::GetFormat()
{
	return format;		 		
}
	
int Instruction::GetLength()
{
	return format;	
}
	// set the operand, what comes after the mneumonic in the source code
void Instruction::SetOperand(string op)
{
	this->operand = op;
}
			// set the format of the instruction (format 1,2, 3, or 4)
void Instruction::SetFormat(int fmt)
{
	this->format = fmt;
	
}

