#pragma once
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include "SymbolTable.h"
#include "ProgramInternalForm.h"
#include "SyntaxErrorException.h"
#include "FiniteAutomaton.h"

class Scanner {
private:
	HashTable<std::string, int> tokens;
	std::vector<std::string> tokensPositionList;
	SymbolTable& symbolTable;
	ProgramInternalForm& programInternalForm;
	FiniteAutomaton variableFA;
	FiniteAutomaton integerFA;
	int lineCount;

	int computePosition(std::string symbol);
	void addIdentifier(std::string identifier);
	ProgramInternalForm::Identifier determineIdentifierType(std::string identifier);
public:
	static int globalTokenId;

	Scanner(std::string tokensFile, SymbolTable& symbolTable, ProgramInternalForm& programInternalForm, std::string variableFAFile, std::string integerFAFile);
	void scan(std::string programFile);
	std::vector<std::string>& getTokensPositionList();
};