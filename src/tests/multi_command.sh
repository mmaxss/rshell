#!/bin/sh

echo a; echo b;
echo a || echo b;
echo a && echo b;

echo a; echo b; echo c;
echo a; echo b || echo c;
echo a; echo b && echo c;
echo a || echo b; echo c;
echo a || echo b && echo c;
echo a || echo b || echo c;
echo a && echo b; echo c;
echo a && echo b || echo c;
echo a && echo b && echo c;


echo a; echo b; echo c; echo d;
echo a; echo b; echo c || echo d;
echo a; echo b; echo c && echo d;
echo a; echo b || echo c; echo d;
echo a; echo b || echo c || echo d;
echo a; echo b || echo c && echo d;
echo a; echo b && echo c; echo d;
echo a; echo b && echo c || echo d;
echo a; echo b && echo c && echo d;

echo a || echo b; echo c; echo d;
echo a || echo b; echo c || echo d;
echo a || echo b; echo c && echo d;
echo a || echo b || echo c; echo d;
echo a || echo b || echo c || echo d;
echo a || echo b || echo c && echo d;
echo a || echo b && echo c; echo d;
echo a || echo b && echo c || echo d;
echo a || echo b && echo c && echo d;

echo a && echo b; echo c; echo d;
echo a && echo b; echo c || echo d;
echo a && echo b; echo c && echo d;
echo a && echo b || echo c; echo d;
echo a && echo b || echo c || echo d;
echo a && echo b || echo c && echo d;
echo a && echo b && echo c; echo d;
echo a && echo b && echo c || echo d;
echo a && echo b && echo c && echo d;