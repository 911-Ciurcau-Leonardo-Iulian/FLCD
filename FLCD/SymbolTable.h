#pragma once
#include "HashTable.cpp"

class SymbolTable {
private:
	HashTable<std::string, int> hashTable;
public:
	static int globalPosition;

	SymbolTable();
	void add(std::string symbol);
	bool contains(std::string symbol);
	int getPosition(std::string symbol);
};