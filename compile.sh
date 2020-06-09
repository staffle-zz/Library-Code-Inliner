#!/bin/bash

./Build/tool < main.template > submit.cpp
g++ -o run submit.cpp -Wall -std=c++17
./run < io/in > io/out
