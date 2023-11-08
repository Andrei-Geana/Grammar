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

std::vector<char> FiniteAutomaton::getFinalStates() const noexcept
{
	return m_finalStates;
}
