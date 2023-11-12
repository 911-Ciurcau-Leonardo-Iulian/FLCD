#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "HashTable.cpp"

class FiniteAutomaton {
private:
	std::vector<std::string> states;
	std::string initialState;
	std::vector<std::string> alphabet;
	HashTable<std::string, std::vector<std::pair<std::string, std::string>>> transitions;
	std::vector<std::string> finalStates;
public:
	enum Stage {
		STATES,
		INITIAL_STATE,
		ALPHABET,
		TRANSITIONS,
		FINAL_STATES
	};

	FiniteAutomaton(std::string inputFile);
	std::vector<std::string>& getStates();
	std::string& getInitialState();
	std::vector<std::string>& getAlphabet();
	HashTable<std::string, std::vector<std::pair<std::string, std::string>>>& getTransitions();
	std::vector<std::string>& getFinalStates();
	void outputStates(std::ostream& out=std::cout);
	void outputInitialState(std::ostream& out=std::cout);
	void outputAlphabet(std::ostream& out=std::cout);
	void outputTransitions(std::ostream& out=std::cout);
	void outputFinalStates(std::ostream& out=std::cout);
};