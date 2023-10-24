#pragma once
#include "Productie.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <regex>

class Gramatica
{
public:
	Gramatica(const std::vector<char>&, const std::vector<char>&, const char&, const std::vector<Productie>&);
	Gramatica();
	friend std::istream& operator>>(std::istream& in, Gramatica&);
	friend std::ostream& operator<<(std::ostream& out, const Gramatica&);

	void setStartCharacter(const char&);
	std::string getCuvant() const;

	//TO BE DONE
	// void verificareValabilitate();
private:
	std::vector<char> m_Vn;
	std::vector<char> m_Vt;
	char m_caracterStart;
	std::vector<Productie> m_productie;
	static const char lamda = '@';

	void stringToVector(const std::string&, const bool&);
	uint16_t getIndiceRandom(const uint16_t&) const;
	void aplicareProductie(const uint16_t&, std::string&) const;
	std::vector<uint16_t> getIndiciAparitii(const uint16_t&, const std::string&) const;
	void replaceInString(const uint16_t&, std::string&, const uint16_t&) const;
	void afisareProductie(const uint16_t&, const std::string&, const uint16_t&) const;
};