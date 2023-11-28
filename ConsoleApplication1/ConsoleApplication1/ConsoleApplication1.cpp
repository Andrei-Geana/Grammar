#include "Grammar.h"
#include "FiniteAutomaton.h"

#include <iostream>

int main()
{
	Grammar grammar;
	grammar.readGrammarFromFile("intrare2.prodb");
	grammar.printGrammar(std::cout);
	try
	{
		if (!grammar.verifyGrammar())
			throw std::exception("ERROR: GRAMMAR IS NOT VALID!");
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << "\n";
		return 1;
	}
	FiniteAutomaton automaton = grammar.grammarToAutomaton();
	automaton.printAutomaton(std::cout);
	std::cout << "\n" << std::boolalpha << automaton.checkWord(automaton.getInitialState(), "aab") << "\n";
	//
	uint16_t n = 5;
	std::unordered_set<std::string> words;
	while (words.size() < 5)
		words.emplace(grammar.generateWord());
	for (const auto& word : words)
		std::cout << word << "\n";
	//
	return 0;
}