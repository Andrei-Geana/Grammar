#include <iostream>
#include <unordered_set>
#include "Grammar.h"

void readGrammarFromFile(const std::string& nume_fisier, Grammar& curenta)
{
	std::ifstream fin{ nume_fisier };
	fin >> curenta;
	fin.close();
}

int main()
{
	Grammar current;
	readGrammarFromFile("intrare2.prodb", current);
	std::cout << current;
	try
	{
		if (!current.GrammarIsValid())
			throw std::exception("ERROR: GRAMMAR IS NOT VALID!");
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << "\n";
		return 1;
	}
	uint16_t n = 5;
	std::unordered_set<std::string> words;
	if (current.GrammarIsRegular() == true)
		std::cout << "YES";
	else
		std::cout << "NO";
	/*
	while (words.size() < 500)
		words.emplace(current.GetCuvant());
	for (const auto& word : words)
		std::cout << word << "\n";
		*/
	return 0;
}