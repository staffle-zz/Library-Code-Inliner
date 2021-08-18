#!/bin/bash
# run this after any change in Code-Generators
g++ Code-Generator/main.cpp -o Build/tool -Wall -std=c++17
g++ Code-Generator/dbg_remover.cpp -o Build/dbgrm -Wall -std=c++17
g++ Code-Generator/optimize.cpp -o Build/final -Wall -std=c++17