#pragma once
#include <string>
#include <map>
#include "Grammar.h"

class CDeterminator
{
public:
	CDeterminator(CGrammar& grammar)
		: m_grammar(grammar)
	{
	};
	CGrammar::DeterministicGrammar Determinate();

private:
	void GetOutsForStartState();
	void GetSimpleOuts();
	void GetCompositeOuts();
	std::string GetResultOut(const std::pair<std::string, std::string>& stateActionPair, const std::string& changeableState = "");
	
	std::set<std::pair<std::string, std::string>> m_keysWithFoundStates;
	CGrammar& m_grammar;
	CGrammar::DeterministicGrammar m_resultGrammar;
};