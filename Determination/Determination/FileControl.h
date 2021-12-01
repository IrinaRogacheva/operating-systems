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
	void WriteGrammar(CGrammar::DeterministicGrammar grammar, std::set<std::string> actions);
private:
	CGrammar::NondeterministicGrammar ReadRightGrammar(const size_t numberOfNonterminals, std::set<std::string>& actions);
	CGrammar::NondeterministicGrammar ReadLeftGrammar(const size_t numberOfNonterminals, std::set<std::string>& actions);

	CGrammar::GrammarType ConvertToGrammarType(const std::string& str);
	int ReadInt();

	void PrintElement(const std::string& str);
	
	std::istream& m_input;
	std::ostream& m_output;
};