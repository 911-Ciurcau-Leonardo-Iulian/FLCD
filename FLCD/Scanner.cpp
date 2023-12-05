#include "Scanner.h"

int Scanner::globalTokenId;

Scanner::Scanner(
	std::string tokensFile, 
	SymbolTable& symbolTable, 
	ProgramInternalForm& programInternalForm,
	std::string variableFAFile,
	std::string integerFAFile
) : symbolTable(symbolTable),
	programInternalForm(programInternalForm),
	lineCount(0),
	variableFA(FiniteAutomaton(variableFAFile)),
	integerFA(FiniteAutomaton(integerFAFile))
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
	lineCount = 0;

	while (std::getline(fin, currentLine))
	{
		lineCount++;
		originalCurrentLine = currentLine;
		char* nextToken = nullptr;
		char* token = STR_TOK_SECURE(const_cast<char*>(currentLine.c_str()), delimiters, &nextToken);

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
						throw SyntaxErrorException("misplaced string", lineCount, currentWord);
					}

					// if we are looking inside a string literal, we have to take spaces into account
					// so we will look into the original string, with spaces
					const char* originalStringPosition = (token + i - currentLine.c_str()) + originalCurrentLine.c_str();
					
					if (strchr(originalStringPosition + 1, '\'') == nullptr)
					{
						// end quote not found
						throw SyntaxErrorException("end quote of string not found", lineCount, originalStringPosition);
					}
					
					char* afterStringToken = nullptr;
					char* stringContent = STR_TOK_SECURE((char*)originalStringPosition + 1, "'", &afterStringToken);
					std::string stringLiteral = "'" + std::string(stringContent) + "'";

					int position = symbolTable.getPosition(stringLiteral);

					if (position < 0)
					{
						position = symbolTable.add(stringLiteral);
					}

					programInternalForm.add(ProgramInternalForm::Identifier::CONSTANT, position);

					nextToken = nullptr;
					token = STR_TOK_SECURE(afterStringToken, delimiters, &nextToken);
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
					// but there could also be the case of false or true, in that case it is a constant
					if (newWord == "true" || newWord == "false")
					{
						addIdentifier(newWord);
					}

					else if (newWord == "//")
					{
						// beginning of comment
						goto next_line_label;
					}

					else
					{
						programInternalForm.add(*tokens.get(newWord), -1);
					}

					currentWord = "";
				}

				else if (tokens.contains(std::string(1, token[i])))
				{
					// if currentWord + token[i] is not from tokens, but token[i] is from tokens,
					// then it means that currentWord is a variable or constant that ends here
					addIdentifier(currentWord);
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
				addIdentifier(currentWord);
			}

			token = STR_TOK_SECURE(nullptr, delimiters, &nextToken);
		}
	next_line_label:
		continue;
	}

	fin.close();
}

void Scanner::addIdentifier(std::string identifier)
{
	int position = computePosition(identifier);
	ProgramInternalForm::Identifier identifierType = determineIdentifierType(identifier);
	programInternalForm.add(identifierType, position);
}

ProgramInternalForm::Identifier Scanner::determineIdentifierType(std::string identifier)
{
	std::string prepared = "";
	for (auto& c : identifier)
	{
		prepared += c;
		prepared += '\n';
	}

	if (isdigit(identifier[0]))
	{

		if (!integerFA.acceptsSequenceFromString(prepared))
		{
			throw SyntaxErrorException("variable cannot start with digit", lineCount, identifier);
		}

		// numeric constant
		return ProgramInternalForm::Identifier::CONSTANT;
	}

	if (identifier[0] == '\'')
	{
		// string constant
		return ProgramInternalForm::Identifier::CONSTANT;
	}

	if (identifier == "true" || identifier == "false")
	{
		// boolean constant
		return ProgramInternalForm::Identifier::CONSTANT;
	}

	if (!variableFA.acceptsSequenceFromString(prepared))
	{
		throw SyntaxErrorException("variable contains invalid characters", lineCount, identifier);
	}

	return ProgramInternalForm::Identifier::ID;
}

std::vector<std::string>& Scanner::getTokensPositionList()
{
	return tokensPositionList;
}