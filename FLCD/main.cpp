#include <iostream>
#include <vector>
#include <cassert>
#include "SymbolTable.h"

int main()
{
	SymbolTable symbolTable = SymbolTable();
	std::vector<std::string> entries = {"a", "b", "c", "\'a string\'", "c'x'", "-12", "true"};
	for (auto& entry : entries)
	{
		symbolTable.add(entry);
	}

	for (int i = 0; i < entries.size(); i++)
	{
		assert((symbolTable.contains(entries[i])));
		assert((symbolTable.getPosition(entries[i]) == i));
	}

	char entryStr[10] = { 0 };
	for (int i = 0; i < 1000; i++)
	{
		sprintf_s(entryStr, "%d", i);
		symbolTable.add(entryStr);
	}

	for (int i = 0; i < 1000; i++)
	{
		sprintf_s(entryStr, "%d", i);
		assert((symbolTable.contains(entryStr)));
		assert((symbolTable.getPosition(entryStr) == i + entries.size()));
	}

	assert((!symbolTable.contains("abcdefg")));
	assert((symbolTable.getPosition("abcdefg") == -1));

	return 0;
}