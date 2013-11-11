#ifndef SOURCECODE_HPP
#define SOURCECODE_HPP

#include <iostream>
#include <map>
#include <vector>
#include "symtable.hpp"
#include "Instruction.hpp"


using namespace std;

class SourceCode
{
public:
		SourceCode(){};
		SourceCode(SymTable ST);
		~SourceCode(){};
		
		vector<Instruction> getInstructions(string objFile);
		bool loadToFile(ofstream,vector<Instruction>);
		void printSourceCode();
		bool generateSourceCode(vector<Instruction>& vec);
		bool loadToFile(string sourceFile);		
	
private:
		SymTable tables;
		vector<string> instructionsFull;
		string progName;
		string progSize;
	
};

#endif
