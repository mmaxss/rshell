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

	bool isSpecial() { //changed the name from Specail to Special
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

	UserCommand(char* c) {
		mult = false;
		char* pch;

		pch = strtok(c, " "); //breaks the sentence when seeing the "" echo "hello" 

		while (pch != NULL) {
			cmds.push_back(new Command(pch));
			pch = strtok(NULL, " ");
		}
		this->isMultiple();
	}

	UserCommand(vector<Command*> cmds) {
		mult = false;
		this->cmds = cmds;
		this->isMultiple();
	}

	~UserCommand() {
		for (unsigned i = 0; i < cmds.size(); ++i) {
			delete cmds.at(i);
		}
	}


	bool isMultiple() {
		for (unsigned i = 0; i < cmds.size(); ++i) {
			if (cmds.at(i)->isSpecial()) {
				return true;
			}
		}

		return false;
	}

	bool isEmpty() {
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
class SeperatedCmd { //should be : public UserCommand
public:
	vector<UserCommand*> cmds;
	vector<int> connectors;

	UserCommand* singleCmds;
	UserCommand* temp;


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

	void setConnectors(char* c) {
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
			if (execute(i) == -1) {
				if (connectors.size() >= (i + 1)) {
					if (connectors.at(i) == 1) {
						break;
					}
				}
			}
			else {
				if (connectors.size() >= (i + 1)) {
					if (connectors.at(i) == 2) {
						break;
					}
				}
			}
		}
	}

	int execute(int i) {
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
				return -1;
			}
			else {
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