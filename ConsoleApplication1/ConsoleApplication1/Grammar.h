#pragma once
#include "Productie.h"
#include "FiniteAutomaton.h"
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
	Grammar() = default;

	void readGrammarFromFile(const std::string& nume_fisier);

	friend std::istream& operator>>(std::istream& in, Grammar&);
	friend std::ostream& operator<<(std::ostream& out, const Grammar&);

	void setStartCharacter(const char&);
	std::string generateWord() const;
	bool canGenerateLambda() const noexcept;

	FiniteAutomaton grammarToAutomaton() const noexcept;

	bool verifyGrammar() const;
	bool isRegular() const;

private:
	static const char k_lambda = '@';
private:
	std::vector<char> m_Vn;
	std::vector<char> m_Vt;
	char m_startCaracter;
	std::vector<Productie> m_productie;

private:
	void initializeVnAndVt(const std::string&, const bool&);
	uint16_t getIndiceRandom(const uint16_t&) const;
	void applyProduction(const uint16_t&, std::string&) const;
	std::vector<uint16_t> getIndiciAparitii(const uint16_t&, const std::string&) const;
	void replaceInString(const uint16_t&, std::string&, const uint16_t&) const;
	void printProduction(const uint16_t&, const std::string&, const uint16_t&) const;

	//Grammar valability check
	bool VnIsPartOfVt() const;
	bool startCaracterIsInVn() const;
	bool everyProductionHasOneVn() const;
	bool existsOneProductionWithStartCaracter() const;
	bool productionsContainOnlyVnAndVt() const;
};