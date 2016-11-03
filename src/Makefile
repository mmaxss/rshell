all: Command_Line rshell


rshell: main.o Command.o
	mkdir bin
	cd bin
	g++ main.o Command.o -o bin/rshell
	
Command_Line: main.o Command.o
	g++ main.o Command.o -o Command_Line

main.o: main.cpp
	g++ -Wall -Werror -ansi -pedantic -c main.cpp

Command.o: Command.cpp
	g++ -Wall -Werror -ansi -pedantic -c Command.cpp
	
clean:
	rm *o hello
	


