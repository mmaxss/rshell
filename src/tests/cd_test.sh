#!/bin/sh

#test real directory and return back
cd src
cd ..

cd bin
cd ..

cd tests
cd ..

cd ..
cd rshell

cd src
cd ..
cd ..
cd rshell

#test unreal directory
cd fakeDir
cd 111
cd ;
cd..
cd .
cd 'src'
cd "src"

#test real directory again after the attempt to cd into unreal directory
cd src
cd ..

cd bin
cd ..

cd tests
cd ..

cd ..
cd rshell

cd src
cd ..
cd ..
cd rshell