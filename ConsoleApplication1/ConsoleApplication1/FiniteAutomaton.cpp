#include "FiniteAutomaton.h"

char FiniteAutomaton::k_lambda{' '};

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

void FiniteAutomaton::SetFinalStates(bool grammarContainsLambda=false) noexcept
{
	m_finalStates.emplace_back(m_possibleStates[m_possibleStates.size()-1]);
	if (grammarContainsLambda)
		m_finalStates.emplace_back(m_initialState);
}

void FiniteAutomaton::SetFunctions(const std::unordered_map<char, std::unordered_map<char, std::vector<char>>>& function) noexcept
{
	m_transitions = function;
}

void FiniteAutomaton::SetLambda(const char& character) noexcept
{
	k_lambda = character;
}


std::vector<char> FiniteAutomaton::GetFinalStates() const noexcept
{
	return m_finalStates;
}

char FiniteAutomaton::GetInitialState() const noexcept
{
	return m_initialState;
}

void FiniteAutomaton::PrintAutomaton(std::ostream& os) const noexcept
{
	os << "AUTOMATON:\n";
	os << *this;
}

bool FiniteAutomaton::WordHasValidCharacters(const std::string& word) const noexcept
{
	for (auto& letter : word)
	{
		auto found = std::find(m_alphabet.begin(), m_alphabet.end(), letter);
		if (found == m_alphabet.end())
			return false;
	}
	return true;
}

bool FiniteAutomaton::CheckWord(const std::string& word) const noexcept
{
	if (word.size() == 1)
		if (word[0] == k_lambda)
			return std::find(m_finalStates.begin(), m_finalStates.end(), m_initialState) != m_finalStates.end();
	if (!WordHasValidCharacters(word))
		return false;
	return CheckValidWord(m_initialState, word);
}

bool FiniteAutomaton::CheckValidWord(const char& currentState, const std::string& currentWord) const noexcept
{
	//std::cout << currentState << " with ";
	if (currentWord.length() == 0 || currentWord[0] == k_lambda)
	{
		if (m_finalStates[0] == currentState)
			return true;
		if(m_finalStates.size()==2)
			if(m_finalStates[1]==currentState)
				return true;
		return false;
	}
	for (const auto& function : m_transitions.at(currentState))
	{
		//std::cout << function.first << " can go in ";
		for (const auto& elements : function.second)
		{
			//std::cout << elements << " ";
			bool found = CheckValidWord(elements, currentWord.substr(1, currentWord.length() - 1));
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
	visitedStates[state] = true;
	if (std::find(m_finalStates.begin(), m_finalStates.end(), state) != m_finalStates.end())
	{
		return true;
	}
	else {
		std::unordered_map<char, std::vector<char>> functie = m_transitions.at(state);
		for (const auto& dreapta : functie)
		{
			for (const auto& nextState : dreapta.second)
			{
				if (!visitedStates[nextState])
				{
				   if(InitialToFinalRoute(visitedStates, nextState))
					   return true;
				}
			}
		}
	}
	return false;
}

bool FiniteAutomaton::IsStateInPossibleStates(const char& state) const noexcept {
	for (const auto& possibleState : m_possibleStates)
	{
		if (possibleState == state) return true;
	}
	return false;
}

bool FiniteAutomaton::IsStateMadeWithAlphabet(const char& state) const noexcept
{
	for (const auto& letter : m_alphabet)
	{
		if (letter == state) return false;
	}
	return true;
}

bool FiniteAutomaton::CheckStatesExistence() const noexcept
{
	return !m_finalStates.empty() && m_initialState !='\0';
}

bool FiniteAutomaton::VerifyAutomaton() const noexcept 
{
	std::unordered_map<char, bool> visitedStates;
	if (m_finalStates.empty()) 
		return false;
	if(!InitialToFinalRoute(visitedStates))
		return false;
	if (!IsStateInPossibleStates(m_initialState))
		return false;
	for (const auto& finalState : m_finalStates)
	{
		if (!IsStateInPossibleStates(finalState))
			return false;
		if (!IsStateMadeWithAlphabet(finalState))
			return false;
	}
	if (!CheckStatesExistence())
		return false;

	return true;
}

bool FiniteAutomaton::IsDeterministic() const noexcept
{
	for (const auto& stateFunction : m_transitions)
	{
		std::unordered_map<char, std::vector<char>> possibleScenarios = stateFunction.second;
		for (const auto& nextState : possibleScenarios)
		{
			if (nextState.second.size() > 1) return false;
		}
	}
	return true;
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
	out << "\nLambda: " << automaton.k_lambda;
	out << "\nFunctions:\n";
	for (const auto& functie : automaton.m_transitions)
	{
		for (const auto& dreapta : functie.second)
		{
			out << "(" << functie.first << ", ";
			out << dreapta.first << ") = { ";
			for (const auto& finala : dreapta.second)
			{
				out << finala << " ";
			}
			out << "}\n";
		}
	}
	out << "Final states = { ";
	for (const auto& element : automaton.m_finalStates)
		out << element << " ";
	out << "}\n";
	return out;
}
