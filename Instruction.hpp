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
	void SetOperand(string op);
	int GetLength();
	
private:
	SymTable Stable;
	string opKey;
	string name;
	int format;
	string operand;
};

#endif // INSTRUCTION_HPP
