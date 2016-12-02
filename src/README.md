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

The purpose of this project is to implement the cd command. The cd command has
3 functions. cd <PATH> will change the current directory to <PATH> if it exists.
cd will change the current directory to the home directory. cd - will change 
the current working directory to the previous working directory. 

This project also implements the display of the current working directory.

To implement the test functionality, the execute function in the Command class
checks whether the command is cd. Next, function of cd is checked. 

First, if nothing is parsed into cpp[1], then the home directory function is 
called. The directory is changed to the HOME directory. Then the OLDPWD is
updated to the previous directory. Finally PWD is updated to the HOME directory. 

Second, the cd - function is checked. If - is in cpp[1], then the directory is
changed into the OLDPWD. Then the OLDPWD and PWD values are swapped. 

Finally, if neither cd nor cd - runs, the cd <PATH> function is executed. The
directory is changed into the one specified. To update the PWD, a 
temporary string concatenates PWD with the input directory. The OLDPWD is given
the value of ppath. 

The display of the current directory was tacked onto line 17 of main.cpp which
also outputs the $.

Currently, the program cannot handle stacking incomplete precedence operators 
with an incomplete test operator and a connector. For example, if the user 
inputs ( [ echo aa || , then the program will do nothing. The precedence 
operators and test operators were implemented without the other in mind, so
when bug testing problems can arise. 