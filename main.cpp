#include "symtable.hpp"
#include "SourceCode.hpp"
#include "fstream"
#include "stdlib.h"

int main(int argc, char** argv)
{
	SymTable table;
	vector<string> vec = table.getStringVec("test.sym");        
	if(!table.createSymTab(vec))
	{
		cerr<<"SYMTABLE ERROR"<<endl;
		exit(1);
	}
	
	vector<string> vec2 = table.getStringVec("opCodes");   
	if(!table.createOpTable(vec2))
	{
			cerr<<"OPCODE ERROR"<<endl;
			exit(1);
	}
	
	SourceCode code(table, "test.obj", "SourceCode.sic");
	code.createInstructions();
	
	code.writeInstructions();
	// vector<string> vec3 = code.getInstructionsHex("objCode.obj");
	// cout<<vec3[0].print();

	// code.generateSourceCode(vec3);
	// code.loadToFile(sourceFile);
	
	return 0;
}
