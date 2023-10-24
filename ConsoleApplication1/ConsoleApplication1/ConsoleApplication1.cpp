#include <iostream>
#include <unordered_set>
#include "Gramatica.h"

void citire_fisier(const std::string& nume_fisier, Gramatica& curenta)
{
	std::ifstream fin{ nume_fisier };
	fin >> curenta;
	fin.close();
}

int main()
{
	Gramatica curenta;
	citire_fisier("intrare2.prodb", curenta);
	std::cout << curenta;
	uint16_t n = 5;
	std::unordered_set<std::string> cuvinte;
	for(int i=0;i<1;i++)
		cuvinte.insert(curenta.getCuvant());
	for (const auto& cuvant : cuvinte)
	{
		std::cout << cuvant << "\n";
		if (cuvant == "aaaaaaabbab") std::cout << "GASIT";
	}
	return 0;
}