#include "Gramatica.h"

Gramatica::Gramatica(const std::unordered_set<char>& Vn, const std::unordered_set<char>& Vt, const std::string& caracterStart, 
	const std::unordered_map<std::string, std::string>& productie) : 
	m_Vn{ Vn }, m_Vt{ Vt }, m_caracterStart{ caracterStart }, m_productie{productie}
{
}

Gramatica::Gramatica()
{
}

void Gramatica::stringToSet(const std::string& sir_caractere, const bool& inVn)
{
	if(inVn)
		for (int index=0;index<sir_caractere.size();index+=2)
		{
			m_Vn.insert(sir_caractere[index]);
		}
	else
		for (int index = 0; index < sir_caractere.size(); index += 2)
		{
			m_Vt.insert(sir_caractere[index]);
		}
}

std::istream& operator>>(std::istream& in, Gramatica& gramatica)
{
	std::string auxiliar;
	std::getline(in, auxiliar);
	gramatica.stringToSet(auxiliar, true);
	std::getline(in, auxiliar);
	gramatica.stringToSet(auxiliar, false);
	std::getline(in, auxiliar);
	gramatica.m_caracterStart = auxiliar;
	std::string stanga, dreapta;
	while (!in.eof())
	{
		in >> stanga >> dreapta;
		gramatica.m_productie[stanga] = dreapta;
		stanga.clear(); dreapta.clear();
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Gramatica& gramatica)
{
	out << "\nGRAMATICA:\n";
	out << "Vn = { ";
	for (const auto& element : gramatica.m_Vn)
		out << element << " ";
	out << "\nVt = { ";
	for (const auto& element : gramatica.m_Vt)
		out << element << " ";
	out << "\nCaracter start: " << gramatica.m_caracterStart;
	out << "\nProductii:\n";
	for (const auto& productie : gramatica.m_productie)
		out << productie.first << " -> " << productie.second << "\n";
	out << "\n";
	return out;
}
