#include <string>
#include <vector>
#include <signal.h>
#include <iostream>
#include "Command.cpp"

using namespace std;

void test(SeperatedCmd* scmd);
void handler(int number);
string semicolonHandler(const string& str);
string commentHandler(const string& str);

int main(int argc, char* argv[]) {


	while (1) {
		signal(SIGINT, handler);
		string str = "";

		cout << "$";

		getline(cin, str); //take in user input
		str = semicolonHandler(str); //check for semicolons
		str = commentHandler(str); //check for comments


		char* c = strdup(str.c_str()); //change the string into a char*
		UserCommand* cmd = new UserCommand(c); //set char* to UserCommand

		if (cmd->isEmpty()) { //check if empty
			exit(0);
		}

		SeperatedCmd* scmd = new SeperatedCmd(cmd); //split the commands into separate commands

		scmd->executeAll(); //execute all the commands

	}





	return 0;
}

string semicolonHandler(const string& s) {
	string str(s);

	for (unsigned i = 0; i < str.size(); ++i) { //insert space after the semicolon
		if (str.at(i) == ';') {
			str.insert(str.begin() + i, ' ');
			i += 1;
		}
	}
	return str;
}

string commentHandler(const string& s) { //only take the string up the the comment marker
	string str(s);

	for (unsigned i = 0; i < str.size(); ++i) {
		if (str.at(i) == '#') {
			str = str.substr(0, i);
			break;
		}
	}

	return str;
}


void test(SeperatedCmd* scmd) {
	for (unsigned i = 0; i < scmd->cmds.size(); ++i) {
		cout << "Command " << i + 1 << " contains " << scmd->cmds.at(i)->cmds.size() << " single words: ";

		for (unsigned j = 0; j < scmd->cmds.at(i)->cmds.size(); ++j) {
			cout << scmd->cmds.at(i)->cmds.at(j)->cmd << ", ";
		}

		cout << endl;
	}

	cout << "they are connected by " << scmd->connectors.size() - 1 << " connectors: ";
	for (unsigned i = 1; i < scmd->connectors.size(); ++i) {
		cout << scmd->connectors.at(i) << ", ";
	}
	cout << endl;
}

void handler(int number) {
	if (number == SIGINT)
	{
		exit(0);
	}
}
