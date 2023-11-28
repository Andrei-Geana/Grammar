#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
class FiniteAutomaton
{
public:
	FiniteAutomaton() = default;


	void setPossibleStates(const std::vector<char>&) noexcept;
	void setAlphabet(const std::vector<char>&) noexcept;
	void setInitialState(const char&) noexcept;
	void setFinalStates(bool) noexcept;
	void setFunctions(const std::unordered_map<char, std::unordered_map<char, std::vector<char>>>&) noexcept;

	std::vector<char> getFinalStates() const noexcept;
	char getInitialState() const noexcept;

	void printAutomaton(std::ostream&) const noexcept;
	bool checkWord(const char&, const std::string&) const noexcept;

	bool InitialToFinalRoute(std::unordered_map<char, bool>& visitedStates, char state) const noexcept;

	bool IsStateInPossibleStates(const char& state) const noexcept;

	bool VerifyAutomaton() const noexcept;

	friend std::ostream& operator << (std::ostream&, const FiniteAutomaton&);
	/*
	bool VerifyAutomaton() const noexcept;
	bool isDeterministic() const noexcept;
	*/

private:
	std::vector<char> m_possibleStates;
	std::vector<char> m_alphabet;
	char m_initialState;
	std::vector<char> m_finalStates;

	//A cu a se poate duce in A,B,C
	//A cu B se poate duce in B, C
	std::unordered_map<char, std::unordered_map<char, std::vector<char>>> m_Functions;

};

