#include "Grammar.h"

CGrammar::NondeterministicGrammar CGrammar::GetGrammar() const
{
	return m_grammar;
}

CGrammar::GrammarType CGrammar::ConvertFromString(const std::string& str) const
{
	if (str == "R")
	{
		return GrammarType::RIGHT;
	}
	else
	{
		return GrammarType::LEFT;
	}
}

CGrammar::GrammarType CGrammar::GetGrammarType() const
{
	return m_type;
}

std::set<std::string> CGrammar::GetActions() const
{
	return m_actions;
}
