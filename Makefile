all: Command_Line rshell


rshell: main.o Command.o
	mkdir bin
	cd bin
	g++ src/main.o src/Command.o -o bin/rshell
	
Command_Line: main.o Command.o
	g++ src/main.o src/Command.o -o Command_Line

main.o: src/main.cpp
	g++ -Wall -Werror -ansi -pedantic -c src/main.cpp

Command.o: src/Command.cpp
	g++ -Wall -Werror -ansi -pedantic -c src/Command.cpp
	
clean:
	rm *o hello
	


