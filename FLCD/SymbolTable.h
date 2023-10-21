#pragma once
#include "HashTable.cpp"

class SymbolTable {
private:
	HashTable<std::string> hashTable = HashTable<std::string>();
public:
	void add(std::string entry);
	bool contains(std::string entry);
	std::pair<int, int> getPosition(std::string entry);
};