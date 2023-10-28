#pragma once
#include "Productie.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <regex>
#include <unordered_set>

class Grammar
{
public:
	Grammar(const std::vector<char>&, const std::vector<char>&, const char&, const std::vector<Productie>&);
	Grammar();
	friend std::istream& operator>>(std::istream& in, Grammar&);
	friend std::ostream& operator<<(std::ostream& out, const Grammar&);

	void SetStartCharacter(const char&);
	std::string GetCuvant() const;

	bool GrammarIsValid() const;

private:
	static const char k_lambda = '@';
private:
	std::vector<char> m_Vn;
	std::vector<char> m_Vt;
	char m_startCaracter;
	std::vector<Productie> m_productie;

private:
	void InitializeVnAndVt(const std::string&, const bool&);
	uint16_t GetIndiceRandom(const uint16_t&) const;
	void ApplyProduction(const uint16_t&, std::string&) const;
	std::vector<uint16_t> GetIndiciAparitii(const uint16_t&, const std::string&) const;
	void ReplaceInString(const uint16_t&, std::string&, const uint16_t&) const;
	void PrintProduction(const uint16_t&, const std::string&, const uint16_t&) const;

	//Grammar valability check
	bool VnIsPartOfVt() const;
	bool StartCaracterIsInVn() const;
	bool EveryProductionHasOneVn() const;
	bool ExistsOneProductionWithStartCaracter() const;
	bool ProductionsContainOnlyVnAndVt() const;
};