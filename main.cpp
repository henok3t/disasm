/* Information about Assignment
	Name: Henok Tadesse
	UserAccount: masc0753
	Partner Name: Joseph Mouawad
	Partner UserAccount: masc0736
	class: cs530
	Assignment: Program Assignment 2
	filename: main.cpp
 */
 
 
#include "Table.hpp"
#include "SourceCode.hpp"
#include <fstream>
#include <stdlib.h>
#include <iostream>

#define OPCODEFILE "opCodes"

int main(int argc, char** argv)
{
	string objectfile, symfile, opcodefile, output;
	
	// handle command line arguments
	if(argc == 1) // no arguments
	{
		objectfile = "test.obj";
		symfile = "test.sym";	
		output = "SourceCode.sic";	
	}
	else if( argc == 2 ) // two arguments not allowed
	{
		cerr<<"Can Disassemble object file without symbol table";
		exit(1);
	}
	else if( argc == 3) // object file and symtable
	{
		objectfile = argv[1];
		symfile = argv[2];
		output = "SourceCode.sic";	
	}
	else if( argc == 4) // also include output name
	{
		objectfile = argv[1];
		symfile = argv[2];
		output = argv[3];	
	}
	else
	{
		cerr<<"Invalid Number of Arguments"<<endl;
		exit(1);
	}
	
	// parse symbol table
	Table table;
	vector<string> vec = table.getStringVec(symfile);        
	if(!table.createSymTab(vec))
	{
		cerr<<"SYMTABLE ERROR"<<endl;
		exit(1);
	}
	
	// parse opcode table
	vector<string> vec2 = table.getStringVec(OPCODEFILE);   
	if(!table.createOpTable(vec2))
	{
			cerr<<"OPCODE ERROR"<<endl;
			exit(1);
	}
	
	// read instructions and create sic source code
	SourceCode code(table, objectfile, output);
	code.createInstructions();
	
	// write to file
	code.writeInstructions();
	
	return 0;
}
