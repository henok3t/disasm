#include "symtable.hpp"

int main(int argc, char** argv)
{
	SymTable table;
	vector<string> vec = table.getStringVec("test.sym");	
	table.createSymTab(vec);	
	table.printSymTab();	
	
	vector<string> vec2 = table.getStringVec("opCodes");
	
	if(!table.createOpTable(vec2))
	{
		cerr<<"OPCODE ERROR"<<endl;
	}
	table.printOptab();
	
	return 0;
}
