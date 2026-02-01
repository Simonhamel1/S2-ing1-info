#!/bin/bash
if [ "$1" == "main" ]; then
    g++ main.cpp 8.cpp -o program && ./program
else
    g++ sort.cpp 8.cpp -o program && ./program 
fi