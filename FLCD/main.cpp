#include "Scanner.h"
#include "FiniteAutomaton.h"
#define outputBool(cond) ((cond) ? "true" : "false")

void pifAndST();
void FA();
void printFAMenu();

int main()
{
	try
	{
		pifAndST();
		std::cout << '\n';
		FA();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

	return 0;
}

void pifAndST()
{
	SymbolTable symbolTable = SymbolTable();
	ProgramInternalForm programInternalForm = ProgramInternalForm();
	Scanner scanner = Scanner("tokens.txt", symbolTable, programInternalForm, "identifierFA.in", "integerFA.in");
	scanner.scan("p2.txt");
	symbolTable.fprint("st.out");
	std::cout << "Symbol Table printed!\n";
	programInternalForm.fprint("pif.out", scanner.getTokensPositionList());
	std::cout << "PIF printed!\n";
}

void FA()
{
	std::string identifierFile;
	std::cout << "enter identifier file: ";
	std::cin >> identifierFile;

	FiniteAutomaton fa(identifierFile);
	std::cout << "Is deterministic: " << outputBool(fa.isDeterministic()) << '\n';
	std::cout << "Accepts good sequence: " << outputBool(fa.acceptsSequenceFromFile("goodSequence.in")) << '\n';
	std::cout << "Accepts bad sequence: " << outputBool(fa.acceptsSequenceFromFile("badSequence.in")) << '\n';
	std::cout << '\n';

	int command;
	do
	{
		printFAMenu();
		std::cin >> command;
		std::cout << '\n';
		switch (command)
		{
		case FiniteAutomaton::Stage::STATES:
			fa.outputStates();
			break;
		case FiniteAutomaton::Stage::INITIAL_STATE:
			fa.outputInitialState();
			break;
		case FiniteAutomaton::Stage::ALPHABET:
			fa.outputAlphabet();
			break;
		case FiniteAutomaton::Stage::TRANSITIONS:
			fa.outputTransitions();
			break;
		case FiniteAutomaton::Stage::FINAL_STATES:
			fa.outputFinalStates();
			break;
		default:
			break;
		}

		std::cout << "\n\n";
	} while (command != 5);
}

void printFAMenu()
{
	std::cout << "0. Show states\n1. Show initial state\n2. Show alphabet\n"
		"3. Show transitions\n4. Show final states\n5. Exit\n\n";
}