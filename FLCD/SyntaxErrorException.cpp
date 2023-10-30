#include "SyntaxErrorException.h"

SyntaxErrorException::SyntaxErrorException(std::string message, int line) 
	: std::exception(("Syntax error at line " + std::to_string(line) + ": " + message).c_str()) {}