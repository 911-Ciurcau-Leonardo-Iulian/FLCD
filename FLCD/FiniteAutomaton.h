#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "HashTable.cpp"

class FiniteAutomaton {
public:
	struct TransitionPart {
		std::string terminal;
		std::string outputState;
	};
private:
	std::vector<std::string> states;
	std::string initialState;
	std::vector<std::string> alphabet;
	HashTable<std::string, std::vector<TransitionPart>> transitions;
	std::vector<std::string> finalStates;

	bool acceptsSequence(std::istream& in);
public:
	enum Stage {
		STATES,
		INITIAL_STATE,
		ALPHABET,
		TRANSITIONS,
		FINAL_STATES
	};

	FiniteAutomaton(std::string inputFile);
	bool isDeterministic();
	bool acceptsSequenceFromFile(std::string inputFile);
	bool acceptsSequenceFromString(std::string sequence);
	std::vector<std::string>& getStates();
	std::string& getInitialState();
	std::vector<std::string>& getAlphabet();
	HashTable<std::string, std::vector<TransitionPart>>& getTransitions();
	std::vector<std::string>& getFinalStates();
	void outputStates(std::ostream& out=std::cout);
	void outputInitialState(std::ostream& out=std::cout);
	void outputAlphabet(std::ostream& out=std::cout);
	void outputTransitions(std::ostream& out=std::cout);
	void outputFinalStates(std::ostream& out=std::cout);
};