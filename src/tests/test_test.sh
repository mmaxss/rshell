#!/bin/sh

test main.cpp
test -e main.cpp
test -e src
test -f main.cpp
test -f src
test -d main.cpp
test -d src

[ main.cpp ]
[ -e main.cpp ]
[ -e src ]
[ -f main.cpp ]
[ -f src ]
[ -d main.cpp ]
[ -d src ]