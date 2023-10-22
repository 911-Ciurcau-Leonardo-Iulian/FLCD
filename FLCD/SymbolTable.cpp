#include "SymbolTable.h"

int SymbolTable::globalPosition;

SymbolTable::SymbolTable()
{
	SymbolTable::globalPosition = 0;
}

void SymbolTable::add(std::string symbol)
{
	hashTable.add(symbol, SymbolTable::globalPosition);
	SymbolTable::globalPosition++;
}

bool SymbolTable::contains(std::string symbol)
{
	return hashTable.contains(symbol);
}

int SymbolTable::getPosition(std::string symbol)
{
	int* value = hashTable.get(symbol);
	return value ? *value : -1;
}