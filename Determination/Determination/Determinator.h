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
	void Determinate();

private:
	CGrammar& m_grammar;
};