 #include <iostream>
#include <map>
#include <vector>


using namespace std;


class Instruction
{
	public:
	Instructuion(){};
	Instructuion(string opKey, SymTable Stable){};
	~Instructuion(){};
	
	string GetName();
	int GetFormat();
	void SetFormat(int);
	void SetOperand(char[] op);
	void 
	
	
	private:
	SymTable Stable;
	string opKey;
	char[10] Name;
	char[3] Format;
	char[100] Operand;
}