#include <iostream>
#include "LineCode.hpp"

using namespace std;

LineCode::LineCode(string l, string insts, string opr)
{
	label = l;
	instruction = insts;
	operand = opr;
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
