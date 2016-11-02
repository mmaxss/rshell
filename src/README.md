this is the README.mThis file should briefly summarize your project. In particular,
it must include a list of known bugs. If you do not have any known bugs, 
then you probably havenot sufficiently tested your code£¡

The purpose of this project is to create a command shell using c++ composite 
pattern. This command shell takes in a set of commands and executes them 
according to the connectors. It is able to handle multiple commands at once.


In Command.cpp, we use 2 composite classes, UserCommand and 
SeperatedCmd and a base class Command. UserCommand has a vector of Commands
that keeps track of information such as multiple, special characters, and 
empty vectors. SeperatedCmd is a composite of user commands that splits
commands from arguments. SeparateCmd also executes these commands after 
separating them from their arguments through the fork() function.

In main.cpp there are 3 functions. There were errors implementing them into
the Command.cpp, so they are implemented in main.cpp The semicolonHandler checks
for semicolons and the commentHandler truncates the commands after the #.
Finally the handler function is the special exit function Ctrl C.

Currently, echo cannot handle strings with spaces. When a command fails, || 
and ; do not run. 
