#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "SymbolTable.h"
#include "ProgramInternalForm.h"

class Scanner {
private:
	HashTable<std::string, int> tokens;
	std::vector<std::string> tokensPositionList;
	SymbolTable& symbolTable;
	ProgramInternalForm& programInternalForm;

	int computePosition(std::string symbol);
public:
	static int globalTokenId;

	Scanner(std::string tokensFile, SymbolTable& symbolTable, ProgramInternalForm& programInternalForm);
	void scan(std::string programFile);
	std::vector<std::string>& getTokensPositionList();
};