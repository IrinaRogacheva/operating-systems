#include "FileControl.h"
#include <exception>
#include <sstream>
#include <algorithm>
#include <set>

CFileControl::CFileControl(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

CGrammar CFileControl::ReadGrammar()
{
	std::string str;
	getline(m_input, str);

	CGrammar::GrammarType type = ConvertToGrammarType(str);

	size_t numberOfNonterminals = ReadInt();

	CGrammar::Grammar grammar;
	std::set<std::string> actions;
	if (type == CGrammar::GrammarType::RIGHT)
	{
		grammar = ReadRightGrammar(numberOfNonterminals, actions);
	}
	else
	{
		grammar = ReadLeftGrammar(numberOfNonterminals, actions);
	}
	return CGrammar (type, numberOfNonterminals, grammar, actions);
}

CGrammar::Grammar CFileControl::ReadRightGrammar(const size_t numberOfNonterminals, std::set<std::string>& actions)
{
	std::string str, state;
	CGrammar::Grammar grammar;

	for (size_t i = 0; i < numberOfNonterminals; i++)
	{
		getline(m_input, state, ' ');
		getline(m_input, str);
		std::istringstream iss(str);
		while (getline(iss, str, '|'))
		{
			if (str.size() == 1)
			{
				str.push_back('H');
			}
			std::string action = { str[0] };
			std::string out = { str[1] };
			grammar.emplace(std::make_pair(state, action), out);
			actions.insert(action);
		}
	}

	for (auto& item : grammar)
	{
		std::cout << item.first.first << " " << item.first.second << " " << item.second << std::endl;
	}
	return grammar;
}

CGrammar::Grammar CFileControl::ReadLeftGrammar(const size_t numberOfNonterminals, std::set<std::string>& actions)
{
	std::string str, out;
	CGrammar::Grammar grammar;

	for (size_t i = 0; i < numberOfNonterminals; i++)
	{
		getline(m_input, out, ' ');
		getline(m_input, str);
		std::istringstream iss(str);
		while (getline(iss, str, '|'))
		{
			if (str.size() == 1)
			{
				str.insert(str.begin(), 'H');
			}
			std::string state = { str[0] };
			std::string action = { str[1] };
			grammar.emplace(std::make_pair(state, action), out);
			actions.insert(action);
		}
	}

	for (auto& item : grammar)
	{
		std::cout << item.first.first << " " << item.first.second << " " << item.second << std::endl;
	}
	return grammar;
}

CGrammar::GrammarType CFileControl::ConvertToGrammarType(const std::string& str)
{
	if (str == "R")
	{
		return CGrammar::GrammarType::RIGHT;
	}
	else
	{
		return CGrammar::GrammarType::LEFT;
	}
}

int CFileControl::ReadInt()
{
	std::string str;
	getline(m_input, str);
	return  std::stoi(str);
}