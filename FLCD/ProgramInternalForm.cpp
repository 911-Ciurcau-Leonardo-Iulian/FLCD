#include "ProgramInternalForm.h"

void ProgramInternalForm::add(int code, int symbolTablePosition)
{
	pif.push_back(PIFItem{ code, symbolTablePosition });
}

void ProgramInternalForm::fprint(std::string outputFile, std::vector<std::string>& tokensPositionList)
{
	std::ofstream fout(outputFile);
	if (!fout.is_open())
	{
		throw std::runtime_error("file could not be opened");
	}

	for (auto& item : pif)
	{
		switch (item.code)
		{
		case Identifier::CONSTANT:
			fout << "constant";
			break;
		case Identifier::ID:
			fout << "id";
			break;
		default:
			fout << tokensPositionList[item.code];
			break;
		}

		fout << ' ' << item.symbolTablePosition << '\n';
	}

	fout.close();
}