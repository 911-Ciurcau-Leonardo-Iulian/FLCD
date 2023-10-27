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
		scanner.scan("p2.txt");
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}

	return 0;
}