all: Command_Line



Command_Line: main.o Command.o
	g++ main.o Command.o -o Command_Line

main: main.cpp
	g++ -Wall -Werror -ansi -pedantic -c main.cpp

Command.o: Command.cpp
	g++ -Wall -Werror -ansi -pedantic -c Command.cpp

clean:
	rm *o hello
