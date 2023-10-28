#include "Grammar.h"

Grammar::Grammar(const std::vector<char>& Vn, const std::vector<char>& Vt, const char& caracterStart,
	const std::vector<Productie>& productie) : 
	m_Vn{ Vn }, m_Vt{ Vt }, m_startCaracter{ caracterStart }, m_productie{productie}
{
}

Grammar::Grammar()
{
	/* EMPTY */
}

void Grammar::InitializeVnAndVt(const std::string& sir_caractere, const bool& inVn)
{
	if (inVn)
		for (int index = 0; index < sir_caractere.size(); index += 2)
		{
			m_Vn.emplace_back(sir_caractere[index]);
		}
	else
		for (int index = 0; index < sir_caractere.size(); index += 2)
		{
			m_Vt.emplace_back(sir_caractere[index]);
		}
}

void Grammar::SetStartCharacter(const char& caracterInceput)
{
	m_startCaracter=caracterInceput;
}

std::string Grammar::GetCuvant() const
{
	if (!this->GrammarIsValid())
		throw std::exception("ERROR: Not able to generate word. Grammar not valid.");
	std::string sir_modificat;
	sir_modificat.push_back(m_startCaracter);
	std::vector<uint16_t> indiceProductiePosibila;
	do
	{
		indiceProductiePosibila.clear();
		for (uint16_t index=0; index<m_productie.size(); index++)
		{
			if (sir_modificat.find(m_productie[index].m_stanga) != std::string::npos)
				indiceProductiePosibila.emplace_back(index);
		}
		if (indiceProductiePosibila.empty())
			break;
		uint16_t indiceRandom = GetIndiceRandom(indiceProductiePosibila.size()-1);
		ApplyProduction(indiceProductiePosibila[indiceRandom], sir_modificat);
	} while (!indiceProductiePosibila.empty());
	return sir_modificat;
}

bool Grammar::GrammarIsValid() const
{
	if (VnIsPartOfVt()) return false;
	if (!StartCaracterIsInVn()) return false;
	if (!EveryProductionHasOneVn()) return false;
	if (!ExistsOneProductionWithStartCaracter()) return false;
	if (!ProductionsContainOnlyVnAndVt()) return false;
	return true;
}

bool Grammar::VnIsPartOfVt() const
{
	for (auto const& caracter : m_Vn)
	{
		if (std::find(m_Vt.begin(), m_Vt.end(), caracter) != m_Vt.end())
			return true;
	}
	return false;
}

bool Grammar::StartCaracterIsInVn() const
{
	return std::find(m_Vn.begin(), m_Vn.end(), m_startCaracter) != m_Vn.end();

}

bool Grammar::EveryProductionHasOneVn() const
{
	for (const auto& productie : m_productie)
	{
		bool hasAtLeastOneCaracter = false;
		for (const auto& caracter : m_Vn)
		{
			if (std::find(productie.m_stanga.begin(), productie.m_stanga.end(), caracter) != productie.m_stanga.end())
			{
				hasAtLeastOneCaracter = true;
				break;
			}
		}
		if (!hasAtLeastOneCaracter)
			return false;
	}
	return true;
}

bool Grammar::ExistsOneProductionWithStartCaracter() const
{
	for (auto const& productie : m_productie)
	{
		if (productie.m_stanga.size() != 1)
			continue;
		if (std::find(productie.m_stanga.begin(), productie.m_stanga.end(), m_startCaracter) != productie.m_stanga.end())
			return true;
	}
	return false;
}

bool Grammar::ProductionsContainOnlyVnAndVt() const
{
	std::unordered_set<char> caractere;
	caractere.emplace(k_lambda);
	for (auto const& caracter : m_Vn)
		caractere.emplace(caracter);
	for (auto const& caracter : m_Vt)
		caractere.emplace(caracter);
	for (auto const& productie : m_productie)
	{
		for (auto const& letter : productie.m_stanga)
		{
			if (caractere.find(letter) == caractere.end())
				return false;
		}
		for (auto const& letter : productie.m_dreapta)
		{
			if (caractere.find(letter) == caractere.end())
				return false;
		}
	}
	return true;
}

uint16_t Grammar::GetIndiceRandom(const uint16_t& maxim) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, maxim);
	return distrib(gen);
}

void Grammar::ApplyProduction(const uint16_t& index_productie, std::string& cuvant_modificat) const
{
	std::vector<uint16_t> indiciAparitii = GetIndiciAparitii(index_productie, cuvant_modificat);
	uint16_t indiceAparitieRandom = GetIndiceRandom(indiciAparitii.size()-1);
	ReplaceInString(index_productie, cuvant_modificat, indiciAparitii[indiceAparitieRandom]);
}

std::vector<uint16_t> Grammar::GetIndiciAparitii(const uint16_t& index_productie, const std::string& cuvant_modificat) const
{
	std::vector<uint16_t> indiciAparitii;
	const std::regex pattern(m_productie[index_productie].m_stanga);
	std::smatch base_match;
	auto it = std::sregex_iterator(cuvant_modificat.begin(), cuvant_modificat.end(), pattern);
	for (it; it != std::sregex_iterator(); it++)
	{
		base_match = *it;
		indiciAparitii.emplace_back(base_match.position());
	}
	return indiciAparitii;
}

void Grammar::ReplaceInString(const uint16_t& index_productie, std::string& cuvant_modificat, const uint16_t& indiceStart) const
{
	//AfisareProductie(index_productie, cuvant_modificat, indiceStart);
	if (m_productie[index_productie].m_dreapta[0] == k_lambda)
	{
		cuvant_modificat.replace(indiceStart,
			m_productie[index_productie].m_stanga.size(), "");
	}
	else
	{
		cuvant_modificat.replace(indiceStart,
			m_productie[index_productie].m_stanga.size(), m_productie[index_productie].m_dreapta);
	}
}

void Grammar::PrintProduction(const uint16_t& index_productie, const std::string& cuvant_modificat, const uint16_t& indiceStart) const
{
	std::cout << "CUVANT CURENT: " << cuvant_modificat << "\n";
	std::cout << "LA INDEXUL " << indiceStart << " SE APLICA " << m_productie[index_productie].m_stanga << " -> " << m_productie[index_productie].m_dreapta <<"\n";
}

std::istream& operator>>(std::istream& in, Grammar& gramatica)
{
	std::string auxiliar;
	std::getline(in, auxiliar);
	gramatica.InitializeVnAndVt(auxiliar, true);
	std::getline(in, auxiliar);
	gramatica.InitializeVnAndVt(auxiliar, false);
	std::getline(in, auxiliar);
	gramatica.m_startCaracter = auxiliar[0];
	{
		std::string stanga, dreapta;
		while (!in.eof())
		{
			in >> stanga >> dreapta;
			gramatica.m_productie.emplace_back(Productie{stanga,dreapta});
		}
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Grammar& gramatica)
{
	out << "GRAMATICA:\n";
	out << "Vn = { ";
	for (const auto& element : gramatica.m_Vn)
		out << element << " ";
	out << "}\nVt = { ";
	for (const auto& element : gramatica.m_Vt)
		out << element << " ";
	out << "}\nCaracter start: " << gramatica.m_startCaracter;
	out << "\nProductii:\n";
	for (const auto& productie : gramatica.m_productie)
		out << productie.m_stanga << " -> " << productie.m_dreapta<< "\n";
	out << "\n";
	return out;
}