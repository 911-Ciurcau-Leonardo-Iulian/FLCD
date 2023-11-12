#include "FiniteAutomaton.h"

void printMenu();

int main()
{
	FiniteAutomaton fa("FA.in");
	std::cout << "Is deterministic: " << fa.isDeterministic() << "\n\n";
	int command;
	do
	{
		printMenu();
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

	return 0;
}

void printMenu()
{
	std::cout << "0. Show states\n1. Show initial state\n2. Show alphabet\n"
		"3. Show transitions\n4. Show final states\n5. Exit\n\n";
}