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
	if (inVn)
		for (int index = 0; index < sir_caractere.size(); index += 2)
		{
			m_Vn.push_back(sir_caractere[index]);
		}
	else
		for (int index = 0; index < sir_caractere.size(); index += 2)
		{
			m_Vt.push_back(sir_caractere[index]);
		}
}

void Gramatica::setStartCharacter(const char& caracterInceput)
{
	m_caracterStart.erase();
	m_caracterStart.push_back(caracterInceput);
}

std::string Gramatica::getCuvant() const
{
	std::string sir_modificat = m_caracterStart;
	std::vector<uint16_t> indice_productie_posibila;
	do
	{
		indice_productie_posibila.clear();
		for (uint16_t index=0; index<m_productie.size(); index++)
		{
			if (sir_modificat.find(m_productie[index].m_stanga) != std::string::npos)
				indice_productie_posibila.push_back(index);
		}
		if (indice_productie_posibila.empty())
			break;
		uint16_t indice_random = get_indice_random(indice_productie_posibila.size()-1);
		aplicare_productie(indice_productie_posibila[indice_random], sir_modificat);
	} while (!indice_productie_posibila.empty());
	return sir_modificat;
}

uint16_t Gramatica::get_indice_random(const uint16_t& maxim) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, maxim);
	return distrib(gen);
}

void Gramatica::aplicare_productie(const uint16_t& index_productie, std::string& cuvant_modificat) const
{
	afisare_productie(index_productie, cuvant_modificat);
	cuvant_modificat.replace(cuvant_modificat.find(m_productie[index_productie].m_stanga),
		m_productie[index_productie].m_stanga.size(), m_productie[index_productie].m_dreapta);
}

void Gramatica::afisare_productie(const uint16_t& index_productie, const std::string& cuvant_modificat) const
{
	std::cout << "CUVANT CURENT: " << cuvant_modificat << "\n";
	std::cout << "SE APLICA " << m_productie[index_productie].m_stanga << " -> " << m_productie[index_productie].m_dreapta << "\n\n";
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
	out << "GRAMATICA:\n";
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
