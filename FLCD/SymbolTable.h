#pragma once
#include <vector>
#include "HashTable.cpp"

class SymbolTable {
private:
	HashTable<std::string, int> hashTable;
	std::vector<std::string> positionList;
public:
	static int globalPosition;

	SymbolTable();
	int add(std::string symbol);
	bool contains(std::string symbol);
	int getPosition(std::string symbol);
	std::string getSymbol(int position);
};