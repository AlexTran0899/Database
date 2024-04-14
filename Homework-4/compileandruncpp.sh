#!/bin/bash
set -e -v
echo "Creating and filling tables from HW3 solution..."
./hw3_soln.sh

echo "Compiling..."
 g++ -Wall -I /usr/include/cppconn odbc_example.cpp -L /usr/lib -l mysqlcppconn -o odbc_example.exe

echo "Running..."
./odbc_example.exe

