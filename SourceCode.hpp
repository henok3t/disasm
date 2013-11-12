#ifndef SOURCECODE_HPP
#define SOURCECODE_HPP

#include <iostream>
#include <map>
#include <vector>
#include "symtable.hpp"
#include "Instruction.hpp"
#include "LineCode.hpp"
#include <fstream>


using namespace std;

class SourceCode
{
public:
		SourceCode(){};
		SourceCode(SymTable ST, string sourcefile, string output);
		~SourceCode(){source.close(); outfile.close();}
		
		void createInstructions();		
		void writeInstructions();		
		void handleHeaderRecord(string& line);
		void handleDefineRecord(string& line);
		void handleReferRecord(string& line);		
		void handleTextRecord(string& line);
		void handleModificationRecord(string& line);
		void handleEndRecord(string& line);
	
private:
		int hex_To_int(char c);
		char int_To_hex(int i);
		vector<int> getBinary(int d);
		string getAddress(char c);
		string getReg(char c);

		SymTable tables;
		ifstream source;
		ofstream outfile;
		vector<LineCode> code;	
};

#endif
