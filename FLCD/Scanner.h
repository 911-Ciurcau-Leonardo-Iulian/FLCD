#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "SymbolTable.h"

class Scanner {
private:
	HashTable<std::string, void*> tokens;
	SymbolTable& symbolTable;
public:
	Scanner(std::string tokensFile, SymbolTable& symbolTable);
	void scan(std::string programFile);
};