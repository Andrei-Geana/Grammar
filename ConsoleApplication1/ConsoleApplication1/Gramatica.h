#pragma once
#include "Productie.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>

class Gramatica
{
public:
	Gramatica(const std::vector<char>&, const std::vector<char>&, const std::string&, const std::vector<Productie>&);
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
	std::string m_caracterStart;
	std::vector<Productie> m_productie;

	void stringToVector(const std::string&, const bool&);
	uint16_t getIndiceRandom(const uint16_t&) const;
	void aplicareProductie(const uint16_t&, std::string&) const;
	void afisareProductie(const uint16_t&, const std::string&) const;
};