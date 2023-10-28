#include "SymbolTable.h"

int SymbolTable::globalPosition;

SymbolTable::SymbolTable()
{
	SymbolTable::globalPosition = 0;
}

int SymbolTable::add(std::string symbol)
{
	hashTable.add(symbol, SymbolTable::globalPosition);
	positionList.push_back(symbol);
	SymbolTable::globalPosition++;
	return SymbolTable::globalPosition - 1;
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

std::string SymbolTable::getSymbol(int position)
{
	return positionList[position];
}

void SymbolTable::fprint(std::string outputFile)
{
	std::ofstream fout(outputFile);
	if (!fout.is_open())
	{
		throw std::runtime_error("file could not be opened");
	}

	for (int i = 0; i < globalPosition; i++)
	{
		fout << i << ' ' << positionList[i] << '\n';
	}

	fout.close();
}