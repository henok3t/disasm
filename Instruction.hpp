 #include <iostream>
#include <map>
#include <vector>


using namespace std;


class Instruction
{
	public:
	Instruction(){};
	Instruction(string opKey, SymTable Stable){};
	~Instruction(){};
	
	string GetName();
	int GetFormat();
	void SetFormat(int);
	void SetOperand(char* op);	
	
private:
	SymTable Stable;
	string opKey;
	char Name[10];
	char Format[3];
	char Operand[100];
};
