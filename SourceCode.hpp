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
		SourceCode(SymTable ST){};
		~SourceCode(){};
		
		vector<Instruction> getInstructions(string objFile);
		bool loadToFile(ofstream,vector<Instruction>);
		void printSourceCode();
	
private:
		SymTable tables;
		vector<string> instructionsFull;
		string progName;
		string progSize;
	
};
