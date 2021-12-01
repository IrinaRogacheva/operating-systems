#include "FileControl.h"
#include <exception>
#include <sstream>
#include <algorithm>
#include <set>
#include <iomanip>

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

	CGrammar::NondeterministicGrammar grammar;
	std::set<std::string> actions;
	if (type == CGrammar::GrammarType::RIGHT)
	{
		grammar = ReadRightGrammar(numberOfNonterminals, actions);
	}
	else
	{
		grammar = ReadLeftGrammar(numberOfNonterminals, actions);
	}

	m_output << "Non-deterministic:" << std::endl;
	for (auto& item : grammar)
	{
		m_output << item.first.first << " " << item.first.second << " " << item.second << std::endl;
	}

	return CGrammar (type, numberOfNonterminals, grammar, actions);
}

void CFileControl::WriteGrammar(CGrammar::DeterministicGrammar grammar, std::set<std::string> actions)
{
	m_output << std::endl << "Deterministic:" << std::endl;
	PrintElement("");
	m_output << std::left;
	for (auto& item : actions)
	{
		PrintElement(item);
	}
	m_output << std::endl;

	std::set<std::string> writtenStates;
	for (auto& item : grammar)
	{
		if (!writtenStates.count(item.first.first))
		{
			writtenStates.insert(item.first.first);
			PrintElement(item.first.first);
			m_output << std::left;
			for (auto& action : actions)
			{
				if (grammar.find({ item.first.first, action }) != grammar.end())
				{
					PrintElement(grammar[{ item.first.first, action }]);
				}
				else
				{
					PrintElement("");
				}
			}
			m_output << std::endl;
		}
	}

}

CGrammar::NondeterministicGrammar CFileControl::ReadRightGrammar(const size_t numberOfNonterminals, std::set<std::string>& actions)
{
	std::string str, state;
	CGrammar::NondeterministicGrammar grammar;

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
	return grammar;
}

CGrammar::NondeterministicGrammar CFileControl::ReadLeftGrammar(const size_t numberOfNonterminals, std::set<std::string>& actions)
{
	std::string str, out;
	CGrammar::NondeterministicGrammar grammar;

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

void CFileControl::PrintElement(const std::string& str)
{
	const char separator = ' ';
	const int width = 6;

	m_output << std::setw(width) << std::setfill(separator) << str;
}
