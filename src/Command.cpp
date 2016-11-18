#include <vector>
#include <iostream>
#include <string>

#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

using namespace std;


//stores individual commands
class Command {

public:
	char* cmd;
	char* cpp[10];

	Command(char* c) {                                                      //set cmd to char pointer cmd in Command data field
		cmd = c;
		this->parse();
	}

	char* getContent() {                                                     //return char pointer which contains the command.
		return cmd;
	}

	int execute() {                                                         //check if this command is test and execute the command
		string str(cpp[0]);
		if (str == "test") {                                                  //call executeTest if true
			executeTest();
			return 0;
		}

		pid_t pid = fork();

		if (pid == 0) {                                                     //child process
			if (execvp(cpp[0], cpp) == -1) {                                //return 1 if fails
				perror("error");
				return 1;
			}
			else {                                                          //return 0 otherwise
				return 0;
			}
		}
		if (pid > 0) {                                                      //parent
			if (wait(0) == -1) {   //wait for child to finish
				perror("wait");
			}
		}
		return 0;
	}



	void parse() {                                                           //parse the command and mark every place with cpp
		cpp[0] = cmd;


		int i = 1;

		while (*cmd != '\0') {
			if (*cmd == ' ' || *cmd == '\t' || *cmd == '\n') {
				*cmd = '\0';
				cpp[i] = cmd + 1;
				i += 1;
			}
			cmd++;

		}
		cpp[i + 1] = '\0';
	}

	int executeTest() {

		pid_t pid = fork();

		if (pid == 0) {                                                     //child

			string testFlag(cpp[1]);
			if (testFlag == "-f") {                                         // check if file exists and is a regular file
				struct stat File;
				string argument(cpp[2]);
				unsigned i = 3;
				while (cpp[i] != '\0') {
					string temp(cpp[i]);
					argument = argument + " " + temp;
					i += 1;
				}

				char* c = strdup(argument.c_str());
				stat(c, &File);
				if (S_ISREG(File.st_mode)) {                                // if the file exists, output true
					cout << "(True)" << endl;
				}

				else {
					cout << "(False)" << endl;
				}
			}

			else if (testFlag == "-d") {                                    // check if directory exists and is a directory
				struct stat dir;
				string argument(cpp[2]);
				unsigned i = 3;
				while (cpp[i] != '\0') {
					string temp(cpp[i]);
					argument = argument + " " + temp;
					i += 1;
				}

				char* c = strdup(argument.c_str());
				stat(c, &dir);
				if (S_ISDIR(dir.st_mode)) {                                 // if the directory exists, output true
					cout << "(True)" << endl;
				}
				else {
					cout << "(False)" << endl;
				}
			}

			else if (testFlag == "-e") {                                    // check if the file or directory exists with -e flag
				struct stat exist;
				string argument(cpp[2]);
				unsigned i = 3;
				while (cpp[i] != '\0') {
					string temp(cpp[i]);
					argument = argument + " " + temp;
					i += 1;
				}

				char* c = strdup(argument.c_str());
				stat(c, &exist);
				if (S_ISDIR(exist.st_mode)) {                               // if it is a directory
					cout << "(True)" << endl;
				}
				else if (S_ISREG(exist.st_mode)) {                          // if it is a file
					cout << "(True)" << endl;
				}
				else { // if neither
					cout << "(False)" << endl;
				}

			}

			else {
				struct stat exist;
				string argument(cpp[1]);
				unsigned i = 2;
				while (cpp[i] != '\0') {
					string temp(cpp[i]);
					argument = argument + " " + temp;
					i += 1;
				}

				char* c = strdup(argument.c_str());
				stat(c, &exist);
				if (S_ISDIR(exist.st_mode)) {                               // if it is a directory
					cout << "(True)" << endl;
				}
				else if (S_ISREG(exist.st_mode)) {                          // if it is a file
					cout << "(True)" << endl;
				}
				else { // if neither
					cout << "(False)" << endl;
				}

			}

			return 0;
		}

		if (pid > 0) {                                                      //parent
			if (wait(0) == -1) {                                            //wait for child to finish
				perror("wait");
			}
		}
		return 0;
	};
};

/*stores a vector of commands, then executes the commands based on the
connectors. Does not contain () which will be handled in multipleCmdl*/
class commandList {

public:
	vector<Command*> commands;                                              //individual commands will be stored inside this vectors
	vector<int> connectors;                                                 //holds ints to distinguish every connectors for their corresponding commands
	string str;

	commandList(const string& str) {                                         //store the whole string of commands into str
		this->str = str;
		testHandler();
		setConnectors();
		parse();
	}

	void addCommand(Command* c) {                                             //push a command onto the vector 
		commands.push_back(c);
	}

	int execute() {                                                         //execute all the commands depending on their corresponding connectors and returned flag of the preview one
		int prev = 0;
		for (unsigned i = 0; i < commands.size(); ++i) {
			unsigned flag = commands.at(i)->execute();
			if (connectors.size() >(i + 1)) {
				if (flag == 1) {
					if (i == 0) {
						prev = flag;
					}
					else if (i > 0) {
						if (connectors.at(i) == 1) {
							prev = 0;
						}
					}

					if (connectors.at(i + 1) == 1) {
						i += 1;
					}
				}
				else if (flag == 0) {
					if (i == 0) {
						prev = flag;
					}
					else if (i > 0) {
						if (connectors.at(i) == 2) {
							prev = 1;
						}
					}

					if (connectors.at(i + 1) == 2) {
						i += 1;
					}
				}
			}
		}
		return prev;
	}

	void parse() {                                                           //seperate commands
		if (isMultiple()) {
			char* pch;
			char* c = strdup(str.c_str());
			pch = strtok(c, ";&|");                                        //break down sentences once ';' '&' or '|' are found

			while (pch != NULL) {
				commands.push_back(new Command(pch));                       //storing the sencece into a new Command object
				pch = strtok(NULL, ";&|");
			}
		}
		else {
			char* c = strdup(str.c_str());
			Command* cmd = new Command(c);
			commands.push_back(cmd);
		}
	}

	void testHandler() {                                                     //replace [xxxx] by "test xxxx" to execute them as the normal test command
		for (unsigned i = 0; i < str.size(); ++i) {
			if (str.at(i) == '[') {
				for (unsigned j = i; j < str.size(); ++j) {
					if (str.at(j) == ']') {
						string temp = "test ";
						if (str.at(i + 1) == ' ') {
							temp = temp + str.substr(i + 2, j - i - 2);
						}
						else {
							temp = temp + str.substr(i + 1, j - i - 1);
						}

						if (temp.at(temp.size() - 1) == ' ') {
							temp = temp.substr(i, temp.size() - 1);
						}

						str.erase(i, j - i + 1);
						str.insert(i, temp);
					}
				}
			}
		}
	}

	bool isMultiple() {                                                      // check if the str contains more than one commands
		int j = 0;
		int i = findSpecial(str, j);
		bool flag;
		if (i == -1) {
			flag = false;;
		}
		else {
			flag = true;
		}
		return flag;
	}

	void setConnectors() {                                                  // set the vector of connectors into corresponding values.
		connectors.push_back(1);
		for (unsigned i = 0; i < str.length(); ++i) {
			if (str.at(i) == ';') {
				connectors.push_back(0);                                        //connectors store 0 if the cmds are connected by ";""
			}
			else if (str.at(i) == '&') {                                             //connectors store 1 if the cmds are connected by "&&""
				connectors.push_back(1);
				i += 1;
			}
			else if (str.at(i) == '|') {                                             //connectors store 2 if the cmds are connected by "||""
				connectors.push_back(2);
				i += 1;
			}
		}
	}

	int findSpecial(const string& str, int& length) {                        //return the index of first connector
		char* ch;
		for (unsigned i = 0; i < str.length(); ++i) {
			ch = new char(str.at(i));
			if (isSpecial(ch)) {
				if ((*ch == '|') || (*ch == '&')) {
					length = 2;
				}
				else {
					length = 1;
				}
				return i;
			}
		}
		return -1;
	}

	bool isSpecial(char* c) {                                                // check if one char is connector
		bool flag;
		if ((*c == '|') || (*c == '&') || (*c == ';')) {
			flag = true;
		}
		else {
			flag = false;
		}
		return flag;
	}
};


/*
it holds a whole string of commands with or without ().
Make commandList objects once there is commands inside () and excute them.
*/
class multipleCmdl {
public:
	vector<commandList*> cmls;
	vector<int> connectors;
	string str;

	multipleCmdl(const string& str) {                                        //store the string of commands into str
		this->str = str;
		strFormat();
		parse();

	}

	void parse() {                                                           //format the string. Create commandList objects storing in vector cmls
		unsigned i = 0;

		connectors.push_back(1);
		while (i < str.size()) {
			if (str.at(i) == '(') {
				for (unsigned j = i; j < str.size(); j++) {
					if (str.at(j) == ')') {
						commandList* clp = new commandList(str.substr(i + 1, j - i - 1));
						cmls.push_back(clp);

						i = 0;

						if (str.size() == j + 1) {
							str = "";
						}
						else if (str.at(j + 1) == ';') {
							str = str.substr(j + 2, str.size() - j - 1);
							setConnectors(0);
						}
						else if (str.at(j + 1) == '&') {
							str = str.substr(j + 3, str.size() - j - 2);
							setConnectors(1);
						}
						else if (str.at(j + 1) == '|') {
							str = str.substr(j + 3, str.size() - j - 2);
							setConnectors(2);
						}

						break;
					}
				}
			}
			else {
				i++;
			}
		}
		if (str != "") {
			cmls.push_back(new commandList(str));
		}
	}

	void setConnectors(int i) {                                              //set the corresponding connectors.
		connectors.push_back(i);
	}

	void strFormat() {                                                       //handle the spaces inside string and make strings unified.
		std::size_t found = str.find(";");
		while (found != string::npos) {
			if (str.at(found + 1) == ' ') {
				str.erase(found + 1, 1);
			}
			if (str.at(found - 1) == ' ') {
				str.erase(found - 1, 1);
			}

			found = str.find(";", found + 1);
		}

		found = str.find("&&");
		while (found != string::npos) {
			if (str.at(found - 1) == ' ') {
				str.erase(found - 1, 1);

				if (str.at(found + 1) == ' ') {
					str.erase(found + 1, 1);
				}

			}
			else if (str.at(found + 2) == ' ') {
				str.erase(found + 2, 1);
			}

			found = str.find("&&", found + 2);
		}

		found = str.find("||");
		while (found != string::npos) {
			if (str.at(found - 1) == ' ') {
				str.erase(found - 1, 1);
				if (str.at(found + 1) == ' ') {
					str.erase(found + 1, 1);
				}
			}
			else if (str.at(found + 2) == ' ') {
				str.erase(found + 2, 1);
			}
			found = str.find("||", found + 1);
		}
	}

	void execute() {                                                         //execute all the commands depending on their corresponding connectors and returned flag of the preview one
		for (unsigned i = 0; i < cmls.size(); ++i) {
			unsigned flag = cmls.at(i)->execute();
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


};