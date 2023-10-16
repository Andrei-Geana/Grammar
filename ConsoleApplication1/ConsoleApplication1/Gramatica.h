#pragma once
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <regex>
#include <fstream>
#include "Productie.h"

class Gramatica
{
public:
	Gramatica(const std::vector<char>&, const std::vector<char>&, const std::string&, const std::vector<Productie>&);
	Gramatica();
	friend std::istream& operator>>(std::istream& in, Gramatica&);
	friend std::ostream& operator<<(std::ostream& out, const Gramatica&);
private:
	std::vector<char> m_Vn;
	std::vector<char> m_Vt;
	std::string m_caracterStart;
	std::vector<Productie> m_productie;

	void stringToSet(const std::string&, const bool&);
};