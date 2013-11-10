#include "symtable.hpp"

int main(int argc, char** argv)
{
	SymTable table;
	vector<string> vec = table.getStringVec("test.sym");
	table.createSymTab(vec);
	table.printSymTab();
	return 0;
}
