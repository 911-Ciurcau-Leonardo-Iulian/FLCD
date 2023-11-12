#include "FiniteAutomaton.h"

int main()
{
	FiniteAutomaton fa("FA.in");
	int command;
	do
	{
		std::cout << "0. Show states\n1. Show initial state\n2. Show alphabet\n3. Show transitions\n4. Show final states\n5. Exit\n\n";
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