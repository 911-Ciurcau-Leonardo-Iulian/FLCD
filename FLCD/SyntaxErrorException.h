#include <stdexcept>
#include <string>

class SyntaxErrorException : public std::runtime_error {
public:
	SyntaxErrorException(std::string message, int line, std::string identifier);
};