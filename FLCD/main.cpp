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
		{
			auto& states = fa.getStates();
			for (auto& state : states)
			{
				std::cout << state << ' ';
			}
		}
			break;
		case FiniteAutomaton::Stage::INITIAL_STATE:
		{
			std::cout << fa.getInitialState();
		}
			break;
		case FiniteAutomaton::Stage::ALPHABET:
		{
			auto& alphabet = fa.getAlphabet();
			for (auto& terminal : alphabet)
			{
				std::cout << terminal << ' ';
			}
		}
			break;
		case FiniteAutomaton::Stage::TRANSITIONS:
		{
			auto& states = fa.getStates();
			auto& transitions = fa.getTransitions();
			for (auto& state : states)
			{
				auto currentTransitions = transitions.get(state);
				if (currentTransitions != nullptr)
				{
					for (auto& transition : *currentTransitions)
					{
						std::cout << state << ' ' << transition.first << ' ' << transition.second << '\n';
					}
					std::cout << '\n';
				}
			}
		}
			break;
		case FiniteAutomaton::Stage::FINAL_STATES:
		{
			auto& states = fa.getFinalStates();
			for (auto& state : states)
			{
				std::cout << state << ' ';
			}
		}
		break;
		default:
			break;
		}

		std::cout << "\n\n";
	} while (command != 5);

	return 0;
}