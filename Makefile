CC=g++

dasmmake: main.o symtable.o
	$(CC) main.o symtable.o -o dasm

main.o: main.cpp
	$(CC) -c main.cpp

symtable.o: symtable.cpp
	$(CC) -c symtable.cpp
