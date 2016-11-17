#!/bin/sh
echo aa#sadd
echo aa #sadd
echo aa# sadd
echo aa # sadd

echo aa; echo bb#sadd
echo aa; echo bb #sadd
echo aa; echo bb# sadd
echo aa; echo bb # sadd

echo aa; echo bb #sadd ;echo abd
echo aa; echo bb #sadd ;echo abd
echo aa; echo bb# sadd ;echo abd
echo aa; echo bb # sadd ;echo abd 

test main.cpp #happy
test #apples
test -#apples
test -e #apples
test -f #apples
test -g #apples

[ Command.cpp ] #happy
[ #apples ]
[ a#pples ]
[ apples  #]
[ -#apples ]
[ -e#apples ]
[ -f#apples ]
[ -d#apples ]

(echo a || echo b) || echo c
(echo a || #echo b) && echo c
(echo a || echo b) #&& echo c