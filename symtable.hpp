#include <iostream>
#include <map>
#include <vector>

using namespace std;

class SymTable
{
public:
	SymTable(){};
	~SymTable(){};
	
	vector<string> getStringVec(string filename);
	bool createSymTab(vector<string>& vec);
	void printSymTab();
	string getSymbol(string address);
		
private:
	map<string, string> symTab; 
	map<string, string> litTab;
};
