Copyright (C) 2016  Xufei Wang, Andrew Apostol

    This file is part of Command.
    Command is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


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

Currently, the program cannot handle strings with spaces. However, the program
can handle spaces when input from the shell. When testing through shell, the
output of the shell is different than manual inputs into the rshell console.

For example, if we have

echo aa#sadd 

inside our shell, the output is 

aa#sadd

However, when manually input into the rshell console, the output is

aa

