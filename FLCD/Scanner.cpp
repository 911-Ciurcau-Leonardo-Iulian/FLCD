#include "Scanner.h"

int Scanner::globalTokenId;

Scanner::Scanner(std::string tokensFile, SymbolTable& symbolTable, ProgramInternalForm& programInternalForm) : 
	symbolTable(symbolTable), programInternalForm(programInternalForm)
{
	std::ifstream fin(tokensFile);
	std::string currentToken;

	if (!fin.is_open())
	{
		throw std::runtime_error(tokensFile + " could not be opened");
	}

	Scanner::globalTokenId = 0;

	while (fin >> currentToken)
	{
		tokens.add(currentToken, globalTokenId);
		tokensPositionList.push_back(currentToken);
		globalTokenId++;
	}

	fin.close();
}

int Scanner::computePosition(std::string symbol)
{
	int position = symbolTable.getPosition(symbol);

	if (position < 0)
	{
		position = symbolTable.add(symbol);
	}

	return position;
}

void Scanner::scan(std::string programFile)
{
	std::ifstream fin(programFile);

	if (!fin.is_open())
	{
		throw std::runtime_error(programFile + " could not be opened");
	}

	std::string currentLine, originalCurrentLine;
	const char* delimiters = " \t";
	while (std::getline(fin, currentLine))
	{	/// TODO: treat chars, boolean constants
		/// TODO: treat comments
		originalCurrentLine = currentLine;
		char* nextToken = nullptr;
		char* token = strtok_s(const_cast<char*>(currentLine.c_str()), delimiters, &nextToken);
		while (token)
		{
		while_token_label:
			std::string currentWord = "";
			for (int i = 0; token[i]; i++)
			{
				std::string newWord = currentWord + token[i];
				if (token[i] == '\'')
				{
					// beginning of string
					if (tokens.contains(currentWord))
					{
						// before beginning of string we have a reserved word
						programInternalForm.add(*tokens.get(currentWord), -1);
					}
					else if (currentWord.size() > 0)
					{
						// before beginning of string we have an id or const, which is illegal
						throw std::runtime_error("syntax error"); /// TODO: be more explicit
					}
					// if we are looking inside a string literal, we have to take spaces into account
					// so we will look into the original string, with spaces
					const char* originalStringPosition = (token + i - currentLine.c_str()) + originalCurrentLine.c_str();
					char* afterStringToken = nullptr;
					char* stringContent = strtok_s((char*)originalStringPosition + 1, "'", &afterStringToken);
					if (stringContent == nullptr)
					{
						// end quote was not found
						throw std::runtime_error("syntax error"); /// TODO: be more explicit
					}

					std::string stringLiteral = "'" + std::string(stringContent) + "'";
					int position = symbolTable.getPosition(stringLiteral);
					if (position < 0)
					{
						position = symbolTable.add(stringLiteral);
					}
					programInternalForm.add(ProgramInternalForm::Identifier::CONSTANT, position);

					nextToken = nullptr;
					token = strtok_s(afterStringToken, delimiters, &nextToken);
					goto while_token_label;
				}

				else if (tokens.contains(newWord))
				{
					// if currentWord + token[i] is from tokens, check if it belongs to a greater token
					// for example, if currentWord + token[i] = ">", check if it could actually be ">="
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
					// here, newWord is a reserved word, operator, or separator		
					programInternalForm.add(*tokens.get(newWord), -1);
					currentWord = "";
				}

				else if (tokens.contains(std::string(1, token[i])))
				{
					// if currentWord + token[i] is not from tokens, but token[i] is from tokens,
					// then it means that currentWord is a variable or constant that ends here
					int position = computePosition(currentWord);
					programInternalForm.add(-1, position); /// TODO: determine if it is id or const
					currentWord = "";
					i--;
				}

				else 
				{
					// if none of the above are true, keep building currentWord
					currentWord += token[i];
				}
			}
			if (currentWord.size() > 0)
			{
				// if the end of the current line is reached and currentWord is not empty,
				// this means that currentWord is a variable or constant that ends at the end of the line
				int position = computePosition(currentWord);
				programInternalForm.add(-1, position); /// TODO: determine if it is id or const
			}
			token = strtok_s(nullptr, delimiters, &nextToken);
		}
	}

	fin.close();
}

std::vector<std::string>& Scanner::getTokensPositionList()
{
	return tokensPositionList;
}