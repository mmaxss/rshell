#include <stdio.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <vector>
#include <stdlib.h> 
#include <iostream>

#include <signal.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/wait.h>


using namespace std;

//store individual cmd.
class Command {
public:
	char* cmd;

	Command(char* c) {
		cmd = c;
	}

	char* getContent() {
		return cmd;
	}

	bool isSpecial() { //bool function to tell if certain cmd object is special connectors;
		string str(cmd);
		if ((str == "||") || (str == "&&") || (str == ";")) {
			return true;
		}
		return false;
	}

	// virtual void execute() = 0;
	// virtual void parse(Command*) = 0;
	// void 
};

//store all the cmds including special connectors
//no formatting function
class UserCommand {
public:
	vector<Command*> cmds;
	bool mult;

	UserCommand() {
		mult = false;
	}

	UserCommand(char* c) {  //takes a char* and generate a new UserCommand object to store individual cmds.
		mult = false;
		char* pch;

		pch = strtok(c, " "); //breaks the sentence when seeing the "" echo "hello" 

		while (pch != NULL) {
			cmds.push_back(new Command(pch)); // get a new cmd object and store into vector.
			pch = strtok(NULL, " ");
		}
		this->isMultiple();
	}

	UserCommand(vector<Command*> cmds) { //generate another UserCommand object which contains the same cmds;
		mult = false;
		this->cmds = cmds;
		this->isMultiple();
	}

	~UserCommand() {
		for (unsigned i = 0; i < cmds.size(); ++i) {
			delete cmds.at(i);
		}
	}


	bool isMultiple() { // bool function to tell if it is single command or multiple commands.
		for (unsigned i = 0; i < cmds.size(); ++i) {
			if (cmds.at(i)->isSpecial()) {
				return true;
			}
		}

		return false;
	}

	bool isEmpty() { // if the UserCommand is empty.
		if (cmds.size() == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	// void execute(){

	// }
	void parse() {};
};

//format to seperated sentence of commands.
//e.g. : a b || c will be broken down to a b and c.
class SeperatedCmd {
public:
	vector<UserCommand*> cmds;
	vector<int> connectors;

	UserCommand* singleCmds;
	UserCommand* temp;

	//takes UserCommand and breaks it down into seperated commands if it is multiple commands in one line.
	SeperatedCmd(UserCommand* user) {
		if (user->isMultiple()) {
			connectors.push_back(1);                                        //the first element in connectors means whether there are multiple command lines: 1 means there is.
			temp = new UserCommand(user->cmds);                             //make a copy of user's commands;

			for (unsigned i = 0; i < temp->cmds.size(); ++i) {
				if (temp->cmds.at(i)->isSpecial()) {
					setConnectors(temp->cmds.at(i)->getContent());

					singleCmds = new UserCommand();                         //declare a new empty vector of UserCommand pointers for every time the loop is executed.

					for (unsigned j = 0; j < i; ++j) {
						singleCmds->cmds.push_back(temp->cmds.at(0));       //copy all the commands before "||" and "&&" into one vector into singleCmds
						temp->cmds.erase(temp->cmds.begin());
					}

					temp->cmds.erase(temp->cmds.begin());
					this->cmds.push_back(singleCmds);                       //store singleCmds into cmds;
					i = 0;
				}
			}
			this->cmds.push_back(temp);                                     //store the last part of user which should be a single line of commands into cmds.
		}
		else {
			this->cmds.push_back(user);
			this->connectors.push_back(0);
		}
	}

	~SeperatedCmd() {
		if (temp) {
			delete temp;
		}
		if (singleCmds) {
			delete singleCmds;
		}
		for (unsigned i = 0; i < cmds.size(); ++i) {
			for (unsigned j = 0; j < cmds.at(i)->cmds.size(); ++j) {
				delete cmds.at(i)->cmds.at(j);
			}
			delete cmds.at(i);
		}
	}

	void setConnectors(char* c) {   // set the vector of connectors into corresponding values.
		string str(c);

		if (str == ";") {
			connectors.push_back(0);                            //connectors store 0 if the cmds are connected by ";""
		}
		else if (str == "&&") {                                        //connectors store 1 if the cmds are connected by "&&""
			connectors.push_back(1);
		}
		else if (str == "||") {                                   //connectors store 2 if the cmds are connected by "||""
			connectors.push_back(2);
		}
	}

	string getString(unsigned i) {
		string str = "";

		for (unsigned j = 2; j < this->cmds.at(i)->cmds.size(); ++j) { //interate through the vector and append to str
			string temp(this->cmds.at(i)->cmds.at(j)->getContent());
			str = str + temp + " ";
		}
		return str;
	}

	void executeAll() {
		for (unsigned i = 0; i < cmds.size(); ++i) {
			unsigned flag = execute(i);
			if (connectors.size() >(i + 1)) {
				if (flag == 1) {
					if (connectors.at(i + 1) == 1) {
						i += 1;
					}
				}
				else if (flag == 0) {
					if (connectors.at(i + 1) == 2) {
						i += 1;
					}
				}
			}

		}
	}

	unsigned execute(int i) {
		char* firstWord = cmds.at(i)->cmds.at(0)->getContent();
		// string str = getString(i);
		// char * c = new char[str.size() + 1];
		// copy(str.begin(), str.end(), c);
		// c[str.size()] = '\0';

		// char* cpp[] = {c} ;

		char** cpp = new char*[cmds.at(i)->cmds.size()];

		for (unsigned j = 0; j < cmds.at(i)->cmds.size(); ++j) {
			cpp[j] = new char[100];

			cpp[j] = cmds.at(i)->cmds.at(j)->getContent();
		}


		pid_t pid = fork();

		if (pid == 0) {  //child
			if (execvp(firstWord, cpp) == -1) //execute command if no error
			{
				perror("error"); //NEED TO KEEP PERRO
				return 1;
			}
			else {
				cout << "right" << endl;
				return 0;
			}
		}
		if (pid > 0) {   //parent
			if (wait(0) == -1) {   //wait for child to finish
				perror("wait");
			}
		}
		return 0;
	}

};



// void execute(){
//     for(unsigned i = 0; i < cmds.size(); ++i){
//         char* firstWord = cmds.at(i)->cmds.at(0)->getContent();
//         string str = getString(i);
//         char * c = new char[str.size() + 1];
//         copy(str.begin(), str.end(), c);
//         c[str.size()] = '\0';
//         char* cpp[] = {c, NULL} ;

//         // cout << firstWord << endl;
//         // cout << c << endl;

//         pid_t pid = fork();

//         if(pid == 0) //child
//             {
//                 if(execvp(firstWord, cpp) == -1) //execute command if no error
//                     {
//                         perror("error");
//                     }
//         }
//         if(pid > 0) //parent
//         {
//             if(wait(0) == -1) //wait for child to finish
//                 {
//                     perror("wait");
//                 }
//             }
//         }


// }