/* Information about Assignment
	Name: Henok Tadesse
	UserAccount: masc0753
	Partner Name: Joseph Mouawad
	Partner UserAccount: masc0736
	class: cs530
	Assignment: Program Assignment 2
 */
 
#ifndef SYMTABLE_HPP
#define SYMTABLE_HPP

#include <iostream>
#include <map>
#include <vector>

using namespace std;

// struct that consists of the name and format for an opcode
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
	
	// gets vector of strings(words or tokens) for the file name
	vector<string> getStringVec(string filename);
	
	// creates symbol and literal hash table for vector
	bool createSymTab(vector<string>& vec);
	
	// create opcode table from vector
	bool createOpTable(vector<string> vec);
	
	// prints symbol table
	void printSymTab();
	
	// prints operand table
	void printOptab();
	
	// gets the symbol for the given address
	string getSymbol(string address);
	
	// gets the name and format for the opcode provided
	struct opVals getOpVal(string opcode);
	
	// return the symbol table
	map<string, string> getSymTab(){ return symTab; }
		
private:
	map<string, string> symTab; 
	map<string, struct opVals> opTab;
};

#endif
