#include "FiniteAutomaton.h"

FiniteAutomaton::FiniteAutomaton(std::string inputFile)
{
	std::string line;
	std::ifstream fin(inputFile);

	if (!fin.is_open())
	{
		throw std::runtime_error(inputFile + " could not be opened");
	}

	Stage currentReadStage = Stage::STATES;

	while (std::getline(fin, line))
	{
		if (line.empty())
		{
			currentReadStage = (Stage)((int)currentReadStage + 1);
		}
		else 
		{
			const char* delimiters = ",";
			char* nextToken = nullptr;
			char* token = strtok_s(const_cast<char*>(line.c_str()), delimiters, &nextToken);
			while (token)
			{
				switch (currentReadStage)
				{
				case Stage::STATES:
					states.push_back(token);
					break;
				case Stage::INITIAL_STATE:
					initialState = token;
					break;
				case Stage::ALPHABET:
					alphabet.push_back(token);
					break;
				case Stage::TRANSITIONS:
				{
					std::string inState = token;
					token = strtok_s(NULL, delimiters, &nextToken);
					std::string terminal = token;
					token = strtok_s(NULL, delimiters, &nextToken);
					std::string outState = token;
					auto transition = transitions.get(inState);
					if (transition == nullptr)
					{
						transitions.add(inState,
							std::vector<std::pair<std::string, std::string>>{std::make_pair(terminal, outState)}
						);
					}
					else
					{
						transition->push_back(std::make_pair(terminal, outState));
					}
				}
					break;
				case Stage::FINAL_STATES:
					finalStates.push_back(token);
					break;
				default:
					break;
				}
				token = strtok_s(NULL, delimiters, &nextToken);
			}
		}
	}

	fin.close();
}

std::vector<std::string>& FiniteAutomaton::getStates()
{
	return states;
}

std::string& FiniteAutomaton::getInitialState()
{
	return initialState;
}

std::vector<std::string>& FiniteAutomaton::getAlphabet()
{
	return alphabet;
}

HashTable<std::string, std::vector<std::pair<std::string, std::string>>>& FiniteAutomaton::getTransitions()
{
	return transitions;
}

std::vector<std::string>& FiniteAutomaton::getFinalStates()
{
	return finalStates;
}

void FiniteAutomaton::outputStates(std::ostream& out)
{
	for (auto& state : states)
	{
		out << state << ' ';
	}
}

void FiniteAutomaton::outputInitialState(std::ostream& out)
{
	out << initialState;
}

void FiniteAutomaton::outputAlphabet(std::ostream& out)
{
	for (auto& terminal : alphabet)
	{
		std::cout << terminal << ' ';
	}
}

void FiniteAutomaton::outputTransitions(std::ostream& out)
{
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

void FiniteAutomaton::outputFinalStates(std::ostream& out)
{
	for (auto& state : states)
	{
		std::cout << state << ' ';
	}
}
