#include "SyntaxErrorException.h"

SyntaxErrorException::SyntaxErrorException(std::string message, int line, std::string identifier) 
	: std::runtime_error(("Syntax error at line " + std::to_string(line) + ", \"" + identifier + "\": " + message).c_str()) {}