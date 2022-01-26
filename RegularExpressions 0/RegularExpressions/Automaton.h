#pragma once
#include <string>
#include <map>
#include <set>
#include <optional>

class CAutomaton
{
public:
	typedef std::multimap<std::pair<int, std::optional<std::string>>, int> NondeterministicAutomaton;
	typedef std::map<std::pair<std::string, std::string>, std::string> DeterministicGrammar;

	CAutomaton(NondeterministicAutomaton automaton/*, std::set<std::string> actions*/);

	NondeterministicAutomaton GetAutomaton() const;
	std::set<std::string> GetActions() const;

private:
	NondeterministicAutomaton m_automaton;
	std::set<std::string> m_actions;
};