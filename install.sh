#!/bin/bash
# run this after any change in Code-Generators
g++ Code-Generator/main.cpp -o Build/tool.exe -Wall -std=c++17
g++ Code-Generator/dbg_remover.cpp -o Build/dbgrm.exe -Wall -std=c++17
g++ Code-Generator/optimize.cpp -o Build/final.exe -Wall -std=c++17