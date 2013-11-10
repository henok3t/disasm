#include "symtable.hpp"

int main(int argc, char** argv)
{
	SymTable table;
	vector<string> vec = table.getStringVec("test.sym");	
	table.createSymTab(vec);	
	table.printSymTab();	
	
	vector<string> vec2 = table.getStringVec("opCodes");
	table.createOpTable(vec2);
	table.printOptab();
	
	return 0;
}
