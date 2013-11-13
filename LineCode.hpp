/* Information about Assignment
	Name: Henok Tadesse
	UserAccount: masc0753
	Partner Name: Joseph Mouawad
	Partner UserAccount: masc0736
	class: cs530
	Assignment: Program Assignment 2
 */

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
	
	// get the label 
	string getLabel();
	
	// gets the instruction name
	string getInstruction();
	
	// gets the operand
	string getOperand();
	
	// sets the label
	void setLabel(string l);
	
	// sets the instruction name
	void setInstruction(string insts);
	
	// sets the operand to opr
	void setOperand(string opr);
	
	// set to true if instruction is extended e = 1
	bool isExtended;
private:
	string label;
	string instruction;
	string operand;
};


#endif
