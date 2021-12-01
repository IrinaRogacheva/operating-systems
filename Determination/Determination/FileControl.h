#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "Grammar.h"

class CFileControl
{
public:
	CFileControl(std::istream& input, std::ostream& output);
	CGrammar ReadGrammar();
private:
	CGrammar::Grammar ReadRightGrammar(const size_t numberOfNonterminals, std::set<std::string>& actions);
	CGrammar::Grammar ReadLeftGrammar(const size_t numberOfNonterminals, std::set<std::string>& actions);

	CGrammar::GrammarType ConvertToGrammarType(const std::string& str);
	int ReadInt();
	
	std::istream& m_input;
	std::ostream& m_output;
};