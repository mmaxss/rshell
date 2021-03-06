#include <iostream>
#include <string>
#include <string.h>
#include <signal.h>
#include "Command.cpp"
using namespace std;

string commentHandler(const string& s);
void handler(int number);

int main() {
	while (1) {

		signal(SIGINT, handler);                                                //handl exit commands control+c
		string str = "";

		cout << getenv("PWD") << "$ ";
		getline(cin, str);

		str = commentHandler(str);                                              //check for comments

		multipleCmdl* a = new multipleCmdl(str);                                //create new object and execute it
		a->execute();
	}
	return 0;

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

void handler(int number) { //special exit function
	if (number == SIGINT)
	{
		exit(0);
	}
}
