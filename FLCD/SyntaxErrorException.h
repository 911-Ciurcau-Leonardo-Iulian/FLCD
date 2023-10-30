#include <exception>
#include <string>

class SyntaxErrorException : public std::exception {
public:
	SyntaxErrorException(std::string message, int line);
};