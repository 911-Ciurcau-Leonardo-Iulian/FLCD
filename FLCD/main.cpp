#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include "SymbolTable.h"
#include "Scanner.h"

int main()
{
	try 
	{
		SymbolTable symbolTable = SymbolTable();
		ProgramInternalForm programInternalForm = ProgramInternalForm();
		Scanner scanner = Scanner("tokens.txt", symbolTable, programInternalForm);
		scanner.scan("p1.txt");
		symbolTable.fprint("st.out");
		programInternalForm.fprint("pif.out", scanner.getTokensPositionList());
	}
	catch (std::exception& e) 
	{
		std::cout << e.what() << '\n';	
	}

	return 0;
}