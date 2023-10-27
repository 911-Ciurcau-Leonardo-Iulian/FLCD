#include "Scanner.h"

Scanner::Scanner(std::string tokensFile, SymbolTable& symbolTable) : symbolTable(symbolTable)
{
	std::ifstream fin(tokensFile);
	std::string currentToken;

	if (!fin.is_open())
	{
		throw std::runtime_error(tokensFile + " could not be opened");
	}

	while (fin >> currentToken)
	{
		tokens.add(currentToken, nullptr);
	}

	fin.close();
}

void Scanner::scan(std::string programFile)
{
	std::ifstream fin(programFile);

	if (!fin.is_open())
	{
		throw std::runtime_error(programFile + " could not be opened");
	}

	std::string currentLine;
	const char* delimiters = " \t";
	while (std::getline(fin, currentLine))
	{
		char* nextToken = nullptr;
		char* token = strtok_s(const_cast<char*>(currentLine.c_str()), delimiters, &nextToken);
		while (token)
		{
			std::string currentWord = "";
			for (int i = 0; token[i]; i++)
			{
				std::string newWord = currentWord + token[i];
				if (tokens.contains(newWord))
				{
					int j;
					for (j = i + 1; token[j]; j++)
					{
						std::string s = newWord + token[j];
						if (!tokens.contains(s))
						{
							break;
						}
						newWord += token[j];
					}
					i = j - 1;
					std::cout << newWord << '\n';
					currentWord = "";
				}

				else if (tokens.contains(std::string(1, token[i])))
				{
					std::cout << "symbol " << currentWord << '\n';
					currentWord = "";
					i--;
				}

				else 
				{
					currentWord += token[i];
				}
			}
			if (currentWord.size() > 0)
			{
				std::cout << "symbol " << currentWord << '\n';
			}
			token = strtok_s(nullptr, delimiters, &nextToken);
		}
	}

	fin.close();
}