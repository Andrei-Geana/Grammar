#include <iostream>
#include "Gramatica.h"
int main()
{
	Gramatica curenta;
	std::ifstream fin{ "intrare.prodb" };
	fin >> curenta;
	fin.close();
	std::cout << curenta;
	return 0;
}