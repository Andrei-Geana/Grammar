#include "FiniteAutomaton.h"

void FiniteAutomaton::setPossibleStates(const std::vector<char>& characters) noexcept
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

void FiniteAutomaton::setAlphabet(const std::vector<char>& characters) noexcept
{
	m_alphabet = characters;
}


void FiniteAutomaton::setInitialState(const char& character) noexcept
{
	m_initialState = character;
}

void FiniteAutomaton::setFinalStates(bool grammarContainsLambda=false) noexcept
{
	//Adaug doar T momentan
	if (grammarContainsLambda)
		m_finalStates.emplace_back(m_possibleStates[0]);
	m_finalStates.emplace_back(m_possibleStates[m_possibleStates.size()-1]);
}

void FiniteAutomaton::setFunctions(const std::unordered_map<char, std::unordered_map<char, std::vector<char>>>& function) noexcept
{
	m_Functions = function;
}


std::vector<char> FiniteAutomaton::getFinalStates() const noexcept
{
	return m_finalStates;
}

char FiniteAutomaton::getInitialState() const noexcept
{
	return m_initialState;
}

void FiniteAutomaton::printAutomaton(std::ostream& os) const noexcept
{
	os << "AUTOMATON:\n";
	os << *this;
}

bool FiniteAutomaton::checkWord(const char& currentState, const std::string& currentWord) const noexcept
{
	//std::cout << currentState << " with ";
	if (currentWord.length() == 0 || currentWord[0] == '@')
	{
		if (m_finalStates[0] == currentState)
			return true;
		if(m_finalStates.size()==2)
			if(m_finalStates[1]==currentState)
				return true;
		return false;
	}
	for (const auto& function : m_Functions.at(currentState))
	{
		//std::cout << function.first << " can go in ";
		for (const auto& elements : function.second)
		{
			//std::cout << elements << " ";
			bool found = checkWord(elements, currentWord.substr(1, currentWord.length() - 1));
			if (found) return true;
		}
		//std::cout << "\n";
	}
	return false;
}

bool FiniteAutomaton::InitialToFinalRoute(std::unordered_map<char, bool>& visitedStates, char state = '-') const noexcept
{
	if (state == '-')
	{
		state = m_initialState;
	}
	visitedStates.insert({ state,true });
	for (const auto& finalState : m_finalStates)
	{
		if (finalState == state) return true;
	}
	std::unordered_map<char, std::vector<char>> functie = m_Functions.at(state);
	for (const auto& dreapta : functie)
	{
		for (const auto& nextState : dreapta.second)
		{
			if (visitedStates[nextState] == false)
			{
				std::cout << "**";
				InitialToFinalRoute(visitedStates, nextState);
			}
		}
	}
	return false;
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
