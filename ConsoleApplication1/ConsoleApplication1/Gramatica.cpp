#include "Gramatica.h"

Gramatica::Gramatica(const std::vector<char>& Vn, const std::vector<char>& Vt, const std::string& caracterStart,
	const std::vector<Productie>& productie) : 
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
			m_Vn.push_back(sir_caractere[index]);
		}
	else
		for (int index = 0; index < sir_caractere.size(); index += 2)
		{
			m_Vt.push_back(sir_caractere[index]);
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
		gramatica.m_productie.push_back({ stanga,dreapta });
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
	out << "}\nVt = { ";
	for (const auto& element : gramatica.m_Vt)
		out << element << " ";
	out << "}\nCaracter start: " << gramatica.m_caracterStart;
	out << "\nProductii:\n";
	for (const auto& productie : gramatica.m_productie)
		out << productie.m_stanga << " -> " << productie.m_dreapta<< "\n";
	out << "\n";
	return out;
}
