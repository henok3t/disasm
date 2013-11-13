#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <iostream>
#include <map>
#include <vector>


using namespace std;


class Instruction
{
	public:
	Instruction(){};      // default Constructor
	Instruction(string opKey, SymTable Stable);// constructor with an opcode key and a
						// symTable instance containig the
						// corresponding Optable and Symtable
	~Instruction(){};  // default destructor
	
	string GetName();    // returns the Mneumonic of the instruciton
	string GetOperand();
	int GetFormat();// returns the format of the instruction (format 1,2, 3, or 4)
	void SetFormat(int); // set the format of the instruction (format 1,2, 3, or 4)
	void SetOperand(string op);// set the operand, what comes after the mneumonic in the source code
	int GetLength();
	
private:
	SymTable Stable; 
	string opKey; // opOCde
	string name; // Mneunmonic
	int format;  //  format 
	string operand;  // operand, what comes after the mneumonic in the source code
};

#endif // INSTRUCTION_HPP
