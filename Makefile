CC=g++

dasmmake: main.o symtable.o SourceCode.o Instruction.o
	$(CC) main.o symtable.o SourceCode.o Instruction.o -o dasm

main.o: main.cpp
	$(CC) -c main.cpp

symtable.o: symtable.cpp
	$(CC) -c symtable.cpp
	
SourceCode.o: SourceCode.cpp
	$(CC) -c SourceCode.cpp

Instruction.o: Instruction.cpp
	$(CC) -c Instruction.cpp
