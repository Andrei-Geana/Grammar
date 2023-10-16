#include <iostream>
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
	citire_fisier("intrare.prodb", curenta);
	std::cout << curenta;
	return 0;
}