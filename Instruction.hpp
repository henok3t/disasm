#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <iostream>
#include <map>
#include <vector>


using namespace std;


class Instruction
{
	public:
	Instruction(){};
	Instruction(string opKey, SymTable Stable);
	~Instruction(){};
	
	string GetName();
	int GetFormat();
	void SetFormat(int);
	void SetOperand(char* op);
	int GetLength();
	
private:
	SymTable Stable;
	string opKey;
	char Name[10];
	char Format[3];
	char Operand[100];
};

#endif // INSTRUCTION_HPP
