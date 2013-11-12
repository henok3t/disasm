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
	string GetOperand();
	int GetFormat();
	void SetFormat(int);
	void SetOperand(string op);
	int GetLength();
	bool IsIndirect();
	bool IsImmediate();
	bool IsRelative();
	bool IsIndexed();
	bool IsExtended();
	void print();
	
private:
	SymTable Stable;
	string opKey;
	string name;
	int format;
	string operand;
	bool indirect;
	bool immediate;
	bool relative;
	bool indexed;
	bool extended;	
};

#endif // INSTRUCTION_HPP
