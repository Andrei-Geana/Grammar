#pragma once
#include <unordered_map>
#include <string>
class FiniteAutomaton
{
public:
	FiniteAutomaton(const uint16_t&, const std::vector<char>&, const std::string&, const std::vector<std::string>&,
		const std::pair < std::string, std::vector<std::string>>&);

	bool WordIsValid(std::string, const std::string&) const;
private:
	std::vector<std::string> m_Q;
	std::vector<char> m_Sigma;
	std::string m_initialState;
	std::vector<std::string> m_F;
	std::unordered_map<std::string, std::vector<std::string>> m_delta;

};

