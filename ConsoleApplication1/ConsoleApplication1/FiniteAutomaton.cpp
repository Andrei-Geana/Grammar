#include "FiniteAutomaton.h"

char FiniteAutomaton::k_lambda{' '};

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

void FiniteAutomaton::setLambda(const char& character) noexcept
{
	k_lambda = character;
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

bool FiniteAutomaton::wordHasValidCharacters(const std::string& word) const noexcept
{
	for (auto& letter : word)
	{
		auto found = std::find(m_alphabet.begin(), m_alphabet.end(), letter);
		if (found == m_alphabet.end())
			return false;
	}
	return true;
}

bool FiniteAutomaton::checkWord(const std::string& word) const noexcept
{
	if (word.size() == 1)
		if (word[0] == k_lambda)
			return std::find(m_finalStates.begin(), m_finalStates.end(), m_initialState) != m_finalStates.end();
	if (!wordHasValidCharacters(word))
		return false;
	return checkValidWord(m_initialState, word);
}

bool FiniteAutomaton::checkValidWord(const char& currentState, const std::string& currentWord) const noexcept
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
			bool found = checkValidWord(elements, currentWord.substr(1, currentWord.length() - 1));
			if (found) return true;
		}
		//std::cout << "\n";
	}
	return false;
}

//bool FiniteAutomaton::InitialToFinalRoute(std::unordered_map<char, bool>& visitedStates, char state = '-') const noexcept
//{
//	if (state == '-')
//	{
//		state = m_initialState;
//	}
//	visitedStates.insert({ state,true });
//	for (const auto& finalState : m_finalStates)
//	{
//		if (finalState == state) return true;
//	}
//	std::unordered_map<char, std::vector<char>> functie = m_Functions.at(state);
//	for (const auto& dreapta : functie)
//	{
//		for (const auto& nextState : dreapta.second)
//		{
//			if (visitedStates[nextState] == false)
//			{
//				std::cout << "**";
//				InitialToFinalRoute(visitedStates, nextState);
//			}
//		}
//	}
//	return false;
//}

//bool FiniteAutomaton::IsStateInPossibleStates(const char& state) const noexcept {
//	for (const auto& possibleState : m_possibleStates)
//	{
//		if (possibleState == state) return true;
//	}
//	return false;
//}

bool FiniteAutomaton::VerifyAutomaton() const noexcept 
{
	return true;
	/*InitialToFinalRoute;
	IsStateInPossibleStates(m_initialState);
	for (const auto& finalState : m_finalStates)
		IsStateInPossibleStates(finalState);*/
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
