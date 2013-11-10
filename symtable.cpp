#include "symtable.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <fstream>

using namespace std;


vector<string> SymTable::getStringVec(string filename)
{
	ifstream input(filename.c_str(), std::ifstream::in);
	vector<string> tokens;
	char buffer[100];
	char curr = input.get();
	uint16_t index = 0;
	while (curr != EOF)
	{
		if(curr != ' ' && curr != '-' && curr != '\n'  && int(curr) != 13)
		{
			buffer[index] = curr;			
			index++;						
		}
		else
		{
			buffer[index] = '\0';
			if(index != 0)
				tokens.push_back(string(buffer));
			index = 0;
			
		}
		curr = input.get();
	}
	
	return tokens;
}

bool SymTable::createSymTab(vector<string>& vec)
{
	// check if vector entered is a Symbol Table vector
	if(vec[0] != "Symbol")
	{
		return false;
	}
	
	// get the number of symbols
	uint16_t i;
	for(i = 2; i < vec.size(); i++)
	{
		if(vec[i] == "Literal")
		{
			break;
		}
	}	
	uint16_t numOfSym = i - 2;	
	if(numOfSym % 2 == 0)
		numOfSym /= 2;
	else // there is undefined symbol, or address with no symbol
	{
		return false;
	}
	// put symbols into map
	for(i = 0; i < numOfSym*2; i = i + 2)
	{
		symTab[vec[i+3]] = vec[i+2];
	}
	
	// add literals to symbol table
	if( vec.size() > (numOfSym*2)+2 )
	{
		for(i = (numOfSym*2)+4; i < vec.size(); i = i+2)
		{
			symTab[vec[i+1]] = vec[i];
		}
	}
	
	return true;
}

bool SymTable::createOpTable(vector<string> vec)
{
	// check the number of opcodes
	uint16_t numOfOp = vec.size();
	if(numOfOp % 2 == 0)
		numOfOp /= 2;
	else // there is undefined symbol, or address with no symbol
	{
		return false;
	}
	
	// put opcodes into map
	for(int i = 0; i < numOfOp*2; i = i + 2)
	{
		opTab[vec[i+1]] = vec[i];
	}
	return true;
}

void SymTable::printSymTab()
{
	map<string, string>::iterator iter;
	
	cout<<"Symbols:"<<endl;
	for(iter = symTab.begin(); iter != symTab.end(); ++iter)
	{
		cout<<iter->first<<" ";
		cout<<iter->second<<endl;
	}
}

void SymTable::printOptab()
{
	map<string, string>::iterator iter;	
	
	cout<<"OpCodes:"<<endl;
	for(iter = opTab.begin(); iter != opTab.end(); ++iter)
	{
		cout<<iter->first<<" ";
		cout<<iter->second<<endl;
	}
}

string SymTable::getSymbol(string address)
{
	
}
