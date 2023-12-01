#include "Grammar.h"
#include "FiniteAutomaton.h"

#include <iostream>

void displayMenu()
{
	std::cout << "===================== Menu =====================" <<'\n';
	std::cout << "1.Afisarea gramaticii G" << '\n';
	std::cout << "2.Generarea de n cuvinte in gramatica G" << '\n';
	std::cout << "3.Automatul echivalent cu G" << '\n';
	std::cout << "4.Verificarea acceptarii unui cuvant in automat" << '\n';
	std::cout << "5.Generarea unui cuvant in G \n  Verificarea acceptarii unui cuvant in automat " << '\n';
	std::cout << "0.Exit" << '\n';
	std::cout << "================================================" << '\n';
}

int main()
{
	Grammar grammar;
	grammar.ReadGrammarFromFile("intrare2.prodb");
	try
	{
		if (!grammar.VerifyGrammar())
			throw std::exception("ERROR: GRAMMAR IS NOT VALID!");
		if(!grammar.IsRegular())
			throw std::exception("ERROR: GRAMMAR IS NOT REGULAR!");
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << "\n";
		return 1;
	}
	
	FiniteAutomaton automaton = grammar.GrammarToAutomaton();
	if (!automaton.VerifyAutomaton())
	{
		std::cout << "Automaton is not valid.";
		return 1;
	}
	int choice;
	std::string word;
	uint16_t numberOfTries;
	std::unordered_set<std::string> words;
	do {
		displayMenu();
		std::cout << "\nAlege o optiune : ";
		std::cin >> choice;
		std::cout << '\n';
		switch (choice) {
		case 1:
			grammar.PrintGrammar(std::cout);
			break;
		case 2:
			std::cout << "Introduceti valoarea lui n: ";
			uint16_t n;
			numberOfTries=0;
			std::cin >> n;
			while (words.size() < n)
			{
				words.emplace(grammar.GenerateWord());
				if (++numberOfTries > n + 5)
				{
					break;
				}
			}
			if (numberOfTries > n + 5)
				std::cout << "GRAMATICA NU A PUTAT GENERA " << n << " CUVINTE, A GENERAT DOAR:\n";
			for (const auto& word : words)
				std::cout << word << "\n";
			words.clear();
			break;
		case 3:
			automaton.PrintAutomaton(std::cout);
			if (automaton.IsDeterministic())
				std::cout << "\nThe automaton is deterministic.\n";
			else
				std::cout << "\nThe automaton is nondeterministic.\n";
			break;
		case 4:
			std::cout << "Introduceti cuvantul dorit: ";
			std::cin >> word;
			std::cout << "ACCEPTAT: " << std::boolalpha << automaton.CheckWord(word) << "\n";
			break;
		case 5:
			word = grammar.GenerateWord();
			std::cout << "GENERAT: " << word << '\n';
			std::cout << "ACCEPTAT: " << std::boolalpha << automaton.CheckWord(word) << "\n";
			break;
		case 0:
			std::cout << "Ai ales sa iesi din meniu.\n";
			break;
		default:
			std::cout << "Optiune invalida. Alege o optiune valida" << '\n';
			break;
		}
		std::cout << '\n';
	} while (choice != 0);
	return 0;
}