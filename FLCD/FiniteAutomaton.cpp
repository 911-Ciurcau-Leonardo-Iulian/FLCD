#include "FiniteAutomaton.h"

FiniteAutomaton::FiniteAutomaton(std::string inputFile) : transitions(HashTable<std::string, std::vector<TransitionPart>>())
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
			char* token = STR_TOK_SECURE(const_cast<char*>(line.c_str()), delimiters, &nextToken);
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
					token = STR_TOK_SECURE(NULL, delimiters, &nextToken);
					std::string terminal = token;
					token = STR_TOK_SECURE(NULL, delimiters, &nextToken);
					std::string outState = token;
					auto transition = transitions.get(inState);
					if (transition == nullptr)
					{
						transitions.add(inState,
							std::vector<TransitionPart>{{ terminal, outState }}
						);
					}
					else
					{
						transition->push_back({ terminal, outState });
					}
				}
					break;
				case Stage::FINAL_STATES:
					finalStates.push_back(token);
					break;
				default:
					break;
				}
				token = STR_TOK_SECURE(NULL, delimiters, &nextToken);
			}
		}
	}

	fin.close();
}

bool FiniteAutomaton::isDeterministic()
{
	for (auto& state : states)
	{
		auto currentTransitions = transitions.get(state);
		if (currentTransitions != nullptr)
		{
			HashTable<std::string, int> outputStateFrequency;
			for (auto& transition : *currentTransitions)
			{
				if (outputStateFrequency.contains(transition.outputState))
				{
					return false;
				}
				else
				{
					outputStateFrequency.add(transition.outputState, 1);
				}
			}
		}
	}

	return true;
}

bool FiniteAutomaton::acceptsSequenceFromFile(std::string inputFile)
{
	std::ifstream fin(inputFile);
	if (!fin.is_open())
	{
		throw std::runtime_error(inputFile + " could not be opened");
	}
	
	bool accepts = acceptsSequence(fin);
	fin.close();
	return accepts;
}

bool FiniteAutomaton::acceptsSequenceFromString(std::string sequence)
{
	std::istringstream in(sequence);
	return acceptsSequence(in);
}


bool FiniteAutomaton::acceptsSequence(std::istream& in)
{
	std::string currentState = initialState;
	std::string terminal;
	while (std::getline(in, terminal))
	{
		auto currentTransitions = transitions.get(currentState);
		if (currentTransitions == nullptr)
		{
			return false;
		}

		bool found = false;
		for (auto& transitionPart : *currentTransitions)
		{
			if (transitionPart.terminal == terminal)
			{
				currentState = transitionPart.outputState;
				found = true;
				break;
			}
		}

		if (!found)
		{
			return false;
		}
	}

	for (auto& state : finalStates)
	{
		if (state == currentState)
		{
			return true;
		}
	}

	return false;
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

HashTable<std::string, std::vector<FiniteAutomaton::TransitionPart>>& FiniteAutomaton::getTransitions()
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
				std::cout << state << ' ' << transition.terminal << ' ' << transition.outputState << '\n';
			}
			std::cout << '\n';
		}
	}
}

void FiniteAutomaton::outputFinalStates(std::ostream& out)
{
	for (auto& state : finalStates)
	{
		std::cout << state << ' ';
	}
}
