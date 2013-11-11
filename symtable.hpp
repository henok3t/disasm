#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct opVals
{
	string opcode;
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
		
private:
	map<string, string> symTab; 
	map<string, struct opVals> opTab;
};
