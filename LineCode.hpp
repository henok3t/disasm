#ifndef LINECODE_HPP
#define LINECODE_HPP

#include <iostream>

using namespace std;

class LineCode
{
public:
	LineCode(){isExtended = false;}
	LineCode(string l, string insts, string opr);
	~LineCode(){};
	
	string getLabel();
	string getInstruction();
	string getOperand();
	
	void setLabel(string l);
	void setInstruction(string insts);
	void setOperand(string opr);
	
	bool isExtended;
private:
	string label;
	string instruction;
	string operand;
};


#endif
