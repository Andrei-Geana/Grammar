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
	grammar.readGrammarFromFile("intrare2.prodb");
	try
	{
		if (!grammar.verifyGrammar())
			throw std::exception("ERROR: GRAMMAR IS NOT VALID!");
		if(!grammar.isRegular())
			throw std::exception("ERROR: GRAMMAR IS NOT REGULAR!");
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << "\n";
		return 1;
	}
	
	FiniteAutomaton automaton = grammar.grammarToAutomaton();
	int choice;
	std::unordered_set<std::string> words;
	do {
		displayMenu();
		std::cout << "Alege o optiune: ";
		std::cin >> choice;
		std::string word;
		switch (choice) {
		case 1:
			grammar.printGrammar(std::cout);
			break;
		case 2:
			std::cout << "Introduceti valoarea lui n: ";
			uint16_t n;
			std::cin >> n;
			while (words.size() < n)
				words.emplace(grammar.generateWord());
			for (const auto& word : words)
				std::cout << word << "\n";
			words.clear();
			break;
		case 3:
			automaton.printAutomaton(std::cout);
			break;
		case 4:
			std::cout << "Introduceti cuvantul dorit: ";
			std::cin >> word;
			std::cout << "ACCEPTAT: " << std::boolalpha << automaton.checkWord(word) << "\n";
			break;
		case 5:
			word = grammar.generateWord();
			std::cout << "GENERAT: " << word << '\n';
			std::cout << "ACCEPTAT: " << std::boolalpha << automaton.checkWord(word) << "\n";
			break;
		case 0:
			std::cout << "Ai ales sa iesi din meniu.\n";
			break;
		default:
			std::cout << "Optiune invalida. Alege o optiune valida" << '\n';
			break;
		}
	} while (choice != 0);
	return 0;
}