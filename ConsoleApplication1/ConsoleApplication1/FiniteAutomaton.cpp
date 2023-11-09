#include "FiniteAutomaton.h"

void FiniteAutomaton::SetPossibleStates(const std::vector<char>& characters) noexcept
{
	m_possibleStates = characters;
	int i = 0;
	while (i<characters.size())
	{
		char newCharacter = characters[i] + 1;
		auto found = std::find(m_possibleStates.begin(), m_possibleStates.end(), newCharacter);
		if (found == m_possibleStates.end())
		{
			m_possibleStates.emplace_back(newCharacter);
			return;
		}
		i++;
	}
}

void FiniteAutomaton::SetAlphabet(const std::vector<char>& characters) noexcept
{
	m_alphabet = characters;
}


void FiniteAutomaton::SetInitialState(const char& character) noexcept
{
	m_initialState = character;
}

void FiniteAutomaton::SetFinalStates() noexcept
{
	//Adaug doar T momentan
	m_finalStates.emplace_back(m_possibleStates[m_possibleStates.size()-1]);
	/*
	if stanga -> dreapta and dreapta -> lambda
		adaug m_initialState
	*/
}

void FiniteAutomaton::SetFunctions(const std::unordered_map<char, std::unordered_map<char, std::vector<char>>>& function) noexcept
{
	m_Functions = function;
}


std::vector<char> FiniteAutomaton::getFinalStates() const noexcept
{
	return m_finalStates;
}

void FiniteAutomaton::PrintAutomaton() const noexcept
{
	std::cout<< "AUTOMATON:\n";
	std::cout << *this;
}

std::ostream& operator<<(std::ostream& out, const FiniteAutomaton& automaton)
{
	out << "POSSIBLE STATES = { ";
	for (const auto& element : automaton.m_possibleStates)
		out << element << " ";
	out << "}\nALPHABET = { ";
	for (const auto& element : automaton.m_alphabet)
		out << element << " ";
	out << "}\nInitial state: " << automaton.m_initialState;
	out << "\nFunctions:\n";
	for (const auto& functie : automaton.m_Functions)
	{
		out << "(" << functie.first << ", ";
		for (const auto& dreapta : functie.second)
		{
			out << dreapta.first << ") = { ";
			for (const auto& finala : dreapta.second)
			{
				out << finala << " ";
			}
			out << "}";
			//out << "\n";
		}
		out << "\n";
	}
	out << "Final states = { ";
	for (const auto& element : automaton.m_finalStates)
		out << element << " ";
	out << "}\n";
	return out;
}
