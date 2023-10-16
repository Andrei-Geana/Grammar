#pragma once
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <regex>
#include <fstream>
class Gramatica
{
public:
	Gramatica(const std::unordered_set<char>&, const std::unordered_set<char>&, const std::string&, const std::unordered_map<std::string, std::string>&);
	Gramatica();
	friend std::istream& operator>>(std::istream& in, Gramatica&);
	friend std::ostream& operator<<(std::ostream& out, const Gramatica&);
private:
	std::unordered_set<char> m_Vn;
	std::unordered_set<char> m_Vt;
	std::string m_caracterStart;
	std::unordered_map<std::string, std::string> m_productie;

	void stringToSet(const std::string&, const bool&);
};