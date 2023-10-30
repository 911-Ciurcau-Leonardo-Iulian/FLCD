#pragma once
#include <vector>
#include <string>
#include <fstream>

class ProgramInternalForm {
public:
	enum Identifier {
		ID = -1,
		CONSTANT = -2,
	};

	struct PIFItem {
		int code;
		int symbolTablePosition;
	};

private:
	std::vector<PIFItem> pif;

public:
	void add(int code, int symbolTablePosition);
	void fprint(std::string outputFile, std::vector<std::string>& tokensPositionList);
};