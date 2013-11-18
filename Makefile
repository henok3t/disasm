# Name: Henok Tadesse
# UserAccount: masc0753
# Partner Name: Joseph Mouawad
# Partner Account: masc0736
# class: cs530
# Assignment: Program Assignment 1
# filename: main.cpp

CC=g++

dasmmake: main.o Table.o SourceCode.o Instruction.o LineCode.o
	$(CC) main.o Table.o SourceCode.o Instruction.o LineCode.o -o dasm

main.o: main.cpp
	$(CC) -c main.cpp

Table.o: Table.cpp
	$(CC) -c Table.cpp
	
SourceCode.o: SourceCode.cpp
	$(CC) -c SourceCode.cpp

Instruction.o: Instruction.cpp
	$(CC) -c Instruction.cpp
	
LineCode.o: LineCode.cpp
	$(CC) -c LineCode.cpp
	
clean:
	rm main.o Table.o SourceCode.o Instruction.o LineCode.o dasm
