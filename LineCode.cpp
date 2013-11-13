/* Information about Assignment
	Name: Henok Tadesse
	UserAccount: masc0753
	Partner Name: Joseph Mouawad
	Partner UserAccount: masc0736
	class: cs530
	Assignment: Program Assignment 2
 */

#include <iostream>
#include "LineCode.hpp"

using namespace std;

LineCode::LineCode(string l, string insts, string opr)
{
	label = l;
	instruction = insts;
	operand = opr;
	isExtended = false;
}

string LineCode::getLabel()
{
	return label;
}
string LineCode::getInstruction()
{
	return instruction;
}

string LineCode::getOperand()
{
	return operand;
}

void LineCode::setLabel(string l)
{
	label = l;
}

void LineCode::setInstruction(string insts)
{
	instruction = insts;
}

void LineCode::setOperand(string opr)
{
	operand = opr;
}
