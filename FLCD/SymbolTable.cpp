#include "SymbolTable.h"

void SymbolTable::add(std::string entry)
{
	hashTable.add(entry, entry);
}

bool SymbolTable::contains(std::string entry)
{
	return hashTable.contains(entry);
}

std::pair<int, int> SymbolTable::getPosition(std::string entry)
{
	return hashTable.getPosition(entry);
}