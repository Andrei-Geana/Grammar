#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
class FiniteAutomaton
{
public:
	FiniteAutomaton() = default;


	void SetPossibleStates(const std::vector<char>&) noexcept;
	void SetAlphabet(const std::vector<char>&) noexcept;
	void SetInitialState(const char&) noexcept;
	void SetFinalStates(bool) noexcept;
	void SetFunctions(const std::unordered_map<char, std::unordered_map<char, std::vector<char>>>&) noexcept;

	std::vector<char> getFinalStates() const noexcept;

	void PrintAutomaton() const noexcept;

	friend std::ostream& operator << (std::ostream&, const FiniteAutomaton&);

	/*
	bool VerifyAutomaton() const noexcept;
	bool CheckWord(const char&, const std::string&) const noexcept;
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

