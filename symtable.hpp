#ifndef SYMTABLE_HPP
#define SYMTABLE_HPP

#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct opVals
{
	string name;
	int format;
};

class SymTable
{
public:
	SymTable(){};
	~SymTable(){};
	
	vector<string> getStringVec(string filename);
	bool createSymTab(vector<string>& vec);
	bool createOpTable(vector<string> vec);
	void printSymTab();
	void printOptab();
	string getSymbol(string address);
	struct opVals getOpVal(string opcode);
	map<string, string> getSymTab(){ return symTab; }
		
private:
	map<string, string> symTab; 
	map<string, struct opVals> opTab;
};

#endif
