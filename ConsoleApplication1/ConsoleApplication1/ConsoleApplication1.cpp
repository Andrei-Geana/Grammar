#include "Grammar.h"
#include "FiniteAutomaton.h"

#include <iostream>

void ConverGrammarToAutomaton(const Grammar& curenta, FiniteAutomaton& automaton)
{
	automaton.SetPossibleStates(curenta.getVn());
	automaton.SetAlphabet(curenta.getVt());
	automaton.SetInitialState(curenta.getStartCharacter());
	automaton.SetFinalStates();

	//TO BE DONE
	std::unordered_map<char, std::unordered_map<char, std::vector<char>>> transitionFunction;
	std::vector<Productie> productii = curenta.getProductii();
	for (const auto& productie : productii)
	{
		char stanga = productie.m_stanga[0];
		std::string dreapta = productie.m_dreapta;

		if (transitionFunction.find(stanga) == transitionFunction.end())
		{
			std::unordered_map<char, std::vector<char>> emptyMap;
			transitionFunction.emplace(stanga, emptyMap);
		}

		auto* getPossibilities = &transitionFunction[stanga];
		if (dreapta.size() == 1)
		{
			char firstCharacter = dreapta[0];
			if (getPossibilities->find(firstCharacter) == getPossibilities->end())
			{
				std::vector<char> emptyVector;
				getPossibilities->emplace(firstCharacter, emptyVector);
			}
			getPossibilities->at(firstCharacter).emplace_back(automaton.getFinalStates()[0]);
		}
		else
		{
			char firstCharacter = dreapta[0];
			char secondCharacter = dreapta[1];
			if (getPossibilities->find(firstCharacter) == getPossibilities->end())
			{
				std::vector<char> emptyVector;
				getPossibilities->emplace(firstCharacter, emptyVector);
			}
			getPossibilities->at(firstCharacter).emplace_back(secondCharacter);
		}
	}

	for (const auto& functie : transitionFunction)
	{
		std::cout << "PLEC DE LA " << functie.first << " SI CU ";
		for (const auto& dreapta : functie.second)
		{
			std::cout << dreapta.first << " POT AJUNGE LA ";
			for (const auto& finala : dreapta.second)
			{
				std::cout << finala<<" ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

}

int main()
{
	Grammar current;
	current.readGrammarFromFile("intrare2.prodb");
	FiniteAutomaton curenta;
	ConverGrammarToAutomaton(current, curenta);
	std::cout << "\n" << current;
	try
	{
		if (!current.VerifyGrammar())
			throw std::exception("ERROR: GRAMMAR IS NOT VALID!");
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << "\n";
		return 1;
	}
	uint16_t n = 5;
	std::unordered_set<std::string> words;
	while (words.size() < 0)
		words.emplace(current.GenerateWord());
	for (const auto& word : words)
		std::cout << word << "\n";
		
	return 0;
}