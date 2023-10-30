#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "SymbolTable.h"
#include "ProgramInternalForm.h"
#include "SyntaxErrorException.h"

class Scanner {
private:
	HashTable<std::string, int> tokens;
	std::vector<std::string> tokensPositionList;
	SymbolTable& symbolTable;
	ProgramInternalForm& programInternalForm;
	int lineCount;

	int computePosition(std::string symbol);
	void addIdentifier(std::string identifier);
	ProgramInternalForm::Identifier determineIdentifierType(std::string identifier);
public:
	static int globalTokenId;

	Scanner(std::string tokensFile, SymbolTable& symbolTable, ProgramInternalForm& programInternalForm);
	void scan(std::string programFile);
	std::vector<std::string>& getTokensPositionList();
};