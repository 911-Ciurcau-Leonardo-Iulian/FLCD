#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include "SymbolTable.h"
#include "Scanner.h"

int main()
{
	try {
		SymbolTable symbolTable = SymbolTable();
		Scanner scanner = Scanner("tokens.txt", symbolTable);
		scanner.scan("p1.txt");
		for (int i = 0; i < symbolTable.globalPosition; i++)
		{
			std::cout << i << ' ' << symbolTable.getSymbol(i) << '\n';
		}
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}

	return 0;
}