#pragma once
#include <string>
#include <map>
#include <set>

class CGrammar
{
public:
	typedef std::multimap<std::pair<std::string, std::string>, std::string> Grammar;

	enum class GrammarType
	{
		RIGHT,
		LEFT
	};

	CGrammar(GrammarType type, size_t numberOfNonterminals, Grammar grammar, std::set<std::string> actions)
		: m_type(type)
		, m_numberOfNonterminals(numberOfNonterminals)
		, m_grammar(grammar)
		, m_actions(actions)
	{
	};

	Grammar GetGrammar() const;
	GrammarType GetGrammarType() const;
	std::set<std::string> GetActions() const;
	GrammarType ConvertFromString(const std::string& str) const;

private:
	GrammarType m_type;
	size_t m_numberOfNonterminals = 0;
	Grammar m_grammar;
	std::set<std::string> m_actions;
};