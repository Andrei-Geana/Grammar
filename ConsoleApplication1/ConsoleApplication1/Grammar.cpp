#include "Grammar.h"

Grammar::Grammar(const std::vector<char>& Vn, const std::vector<char>& Vt, const char& caracterStart,
	const std::vector<Productie>& productie) : 
	m_Vn{ Vn }, m_Vt{ Vt }, m_startCaracter{ caracterStart }, m_productie{productie}
{
}

void Grammar::PrintGrammar(std::ostream& os) const noexcept
{
	os << "GRAMATICA:\n";
	os << *this;
}

void Grammar::ReadGrammarFromFile(const std::string& nume_fisier)
{
	std::ifstream fin{ nume_fisier };
	fin >> *this;
	fin.close();
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

std::string Grammar::GenerateWord() const
{
	if (!this->VerifyGrammar())
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
	if (sir_modificat.length() == 0)
		return std::string{ k_lambda };
	return sir_modificat;
}

bool Grammar::CanGenerateLambda() const noexcept
{
	auto foundProduction = std::find_if(m_productie.begin(), m_productie.end(), [this](const Productie& productie) {
		if (productie.m_stanga[0] == m_startCaracter)
			if (productie.m_dreapta[0] == k_lambda)
				return true;
		return false;
		});
	if (foundProduction != m_productie.end())
		return true;
	return false;
}

FiniteAutomaton Grammar::GrammarToAutomaton() const noexcept
{
	FiniteAutomaton automaton;
	automaton.SetPossibleStates(m_Vn);
	automaton.SetAlphabet(m_Vt);
	automaton.SetInitialState(m_startCaracter);
	automaton.SetFinalStates(CanGenerateLambda());
	automaton.SetLambda(k_lambda);

	std::unordered_map<char, std::unordered_map<char, std::vector<char>>> transitionFunction;
	std::vector<Productie> productii = m_productie;
	for (const auto& productie : productii)
	{
		char stanga = productie.m_stanga[0];
		std::string dreapta = productie.m_dreapta;

		if (transitionFunction.find(stanga) == transitionFunction.end())
		{
			std::unordered_map<char, std::vector<char>> emptyMap;
			transitionFunction.emplace(stanga, emptyMap);
		}

		auto* getPossibilities = &transitionFunction[stanga];
		if (dreapta.size() == 1)
		{
			char firstCharacter = dreapta[0];
			if (firstCharacter == k_lambda)
				continue;
			if (getPossibilities->find(firstCharacter) == getPossibilities->end())
			{
				std::vector<char> emptyVector;
				getPossibilities->emplace(firstCharacter, emptyVector);
			}
			getPossibilities->at(firstCharacter).emplace_back(automaton.GetFinalStates()[0]);
		}
		else
		{
			char firstCharacter = dreapta[0];
			char secondCharacter = dreapta[1];
			if (getPossibilities->find(firstCharacter) == getPossibilities->end())
			{
				std::vector<char> emptyVector;
				getPossibilities->emplace(firstCharacter, emptyVector);
			}
			getPossibilities->at(firstCharacter).emplace_back(secondCharacter);
		}
	}
	automaton.SetFunctions(transitionFunction);
	return automaton;
}

bool Grammar::VerifyGrammar() const
{
	if (VnIsPartOfVt()) return false;
	if (!StartCaracterIsInVn()) return false;
	if (!EveryProductionHasOneVn()) return false;
	if (!ExistsOneProductionWithStartCaracter()) return false;
	if (!ProductionsContainOnlyVnAndVt()) return false;
	return true;
}

bool Grammar::IsRegular() const
{
	for (const auto& productie : m_productie)
	{
		if (productie.m_stanga.size() != 1) return false;
		if (std::find(m_Vn.begin(), m_Vn.begin(), productie.m_stanga[0]) == m_Vn.end()) return false;
		if (productie.m_dreapta.size() > 2) return false;
		//Case 1 : A -> a or A -> lambda
		if (productie.m_dreapta.size() == 1)
		{
			if (productie.m_dreapta[0] == k_lambda) 
				continue;
			if (std::find(m_Vt.begin(), m_Vt.begin(), productie.m_dreapta[0]) == m_Vt.end()) return false;
			continue;
		}
		//Case 2: A -> aB
		if (std::find(m_Vt.begin(), m_Vt.end(), productie.m_dreapta[0]) == m_Vt.end()) return false;
		if (std::find(m_Vn.begin(), m_Vn.end(), productie.m_dreapta[1]) == m_Vn.end()) return false;
	}
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
	//PrintProduction(index_productie, cuvant_modificat, indiceStart);
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
	out << "Vn = { ";
	for (const auto& element : gramatica.m_Vn)
		out << element << " ";
	out << "}\nVt = { ";
	for (const auto& element : gramatica.m_Vt)
		out << element << " ";
	out << "}\nCaracter start: " << gramatica.m_startCaracter;
	out << "\nLambda: " << gramatica.k_lambda;
	out << "\nProductii:\n";
	for (const auto& productie : gramatica.m_productie)
		out << productie.m_stanga << " -> " << productie.m_dreapta<< "\n";
	return out;
}
