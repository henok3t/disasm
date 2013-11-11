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
        
  		ofstream sourceFile("SourceFile.sic");
        
        SourceCode code(table);
    	vector<string> vec3 = code.getInstructionsHex("objCode.obj");
    	cout<<vec3[0].print();
    
    	code.generateSourceCode(vec3);
    	code.loadToFile(sourceFile);
    
    
        
        return 0;
}
