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

The purpose of this project is to create a test function with the flags of 
-e, -f, and -d, with -e being the default flag. The -e flag checks whether 
the argument exists as a file ordirectory. The -f flag checks whether the 
argument exists as a file. The -d flag checks whether the argument exists 
as a directory.

This project also implements the precedence operator of (). The () operator 
changes the order of returns of the commands. 

To implement the test functionality, the execute function in the Command class
checks whether the command is test. Next it has if else statements checking for
which flag is input. Everything after the flag is checked based on the S_ISDIR
and the S_ISREG functions from the struct status. 

To implement the [] as an alternate way to test functions. We look for the [ 
when taking in input. Everything after the [ until the ] is taken and run 
through the execute function. 

The () operator is immplemented in a similar fashion to the [] function. We 
look for the ( when taking in input, then everything until ) is run through
the parse function. 

Currently, the program cannot handle stacking incomplete precedence operators 
with an incomplete test operator and a connector. For example, if the user 
inputs ( [ echo aa || , then the program will do nothing. The precedence 
operators and test operators were implemented without the other in mind, so
when bug testing problems can arise. 