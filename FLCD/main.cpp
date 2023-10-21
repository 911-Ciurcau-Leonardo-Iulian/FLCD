#include <iostream>
#include <vector>
#include <cassert>
#include "SymbolTable.h"

int main()
{
	SymbolTable symbolTable;
	std::vector<std::string> entries = {"a", "b", "c", "\'a string\'", "c'x'", "-12", "true"};
	for (auto& entry : entries)
	{
		symbolTable.add(entry);
	}

	for (auto& entry : entries)
	{
		assert((symbolTable.contains(entry)));
		assert((symbolTable.getPosition(entry) != std::pair<int, int>{-1, -1}));
	}

	char entryStr[10] = { 0 };
	for (int i = 0; i < 1000; i++)
	{
		sprintf_s(entryStr, "%d", i);
		symbolTable.add(entryStr);
		assert(symbolTable.contains(entryStr));
	}

	for (int i = 0; i < 1000; i++)
	{
		sprintf_s(entryStr, "%d", i);
		assert(symbolTable.contains(entryStr));
		assert((symbolTable.getPosition(entryStr) != std::pair<int, int>{-1, -1}));
	}

	return 0;
}