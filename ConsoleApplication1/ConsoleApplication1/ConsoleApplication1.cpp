#include "Grammar.h"
#include "FiniteAutomaton.h"

#include <iostream>

int main()
{
	Grammar current;
	current.readGrammarFromFile("intrare2.prodb");
	std::cout << current;
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
	FiniteAutomaton curenta = current.GrammarToAutomaton();
	curenta.PrintAutomaton();
	uint16_t n = 5;
	std::unordered_set<std::string> words;
	while (words.size() < 0)
		words.emplace(current.GenerateWord());
	for (const auto& word : words)
		std::cout << word << "\n";
		
	return 0;
}