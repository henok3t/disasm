/* Information about Assignment
	Name: Henok Tadesse
	UserAccount: masc0753
	Partner Name: Joseph Mouawad
	Partner UserAccount: masc0736
	class: cs530
	Assignment: Program Assignment 2
 */
 
#ifndef SOURCECODE_HPP
#define SOURCECODE_HPP

#include <iostream>
#include <map>
#include <vector>
#include "Table.hpp"
#include "Instruction.hpp"
#include "LineCode.hpp"
#include <fstream>


using namespace std;

class SourceCode
{
public:
		SourceCode(){};
		SourceCode(Table ST, string sourcefile, string output);
		~SourceCode(){source.close(); outfile.close();}
		
		// creates the lines of instructions
		void createInstructions();		
		
		// writes the line of instruction to file
		void writeInstructions();				
		
		// reads header record and creates line of instruction
		void handleHeaderRecord(string& line);
		
		// reads text record and creates lines of instructions
		void handleTextRecord(string& line, char* locationCounter);		
		
		// reads End instruciton and creates a line of instruction
		void handleEndRecord(string& line);
	
private:
		// converts a hex digit to int
		int hex_To_int(char c);
		
		// converts a 4 byte hex string to int
		int  hex_to_int(string hex);
		
		// converts and integer 0-15 to hexadecimal equivalent
		char int_To_hex(int i);
		
		// converts d to binary and returns it in binary_opcode
		void getBinary(int d, vector<int>& binary_opcode);
		
		// get the register string for register code
		string getReg(char c);
		
		// adds hexadecimal numbers
		void addHex(char* a, string b, char* sum);
		
		void checkLocationDifference(char* start, const char* end);
		
		
		string programSize;
		Table tables;
		ifstream source;
		ofstream outfile;
		vector<LineCode> code;	
};

#endif
