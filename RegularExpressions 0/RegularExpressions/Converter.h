#pragma once

#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <optional>
#include "Automaton.h"

class CConverter
{
public:
	CConverter(const std::string& expression);
	CAutomaton ConvertExpressionToAutomaton();
	//void WriteGrammar(CGrammar::DeterministicGrammar grammar, std::set<std::string> actions);
private:
	//CGrammar::NondeterministicGrammar ReadRightGrammar(const size_t numberOfNonterminals, std::set<std::string>& actions);
	//CGrammar::NondeterministicGrammar ReadLeftGrammar(const size_t numberOfNonterminals, std::set<std::string>& actions);

	//CGrammar::GrammarType ConvertToGrammarType(const std::string& str);
	void ProcessExpression(CAutomaton::NondeterministicAutomaton& automaton);

	void ProcessAsterisk(CAutomaton::NondeterministicAutomaton& automaton, std::optional<char> action = std::nullopt);
	void ProcessPlusSign(CAutomaton::NondeterministicAutomaton& automaton);
	void ProcessOr(CAutomaton::NondeterministicAutomaton& automaton);
	void ProcessSimpleTransition(CAutomaton::NondeterministicAutomaton& automaton);
	void ProcessBracket(CAutomaton::NondeterministicAutomaton& automaton);

	void CheckIsOrTheLastOperationInBracket(size_t posOfClosingBracket);
	bool CheckIsNextOperationRecursive();

	int ReadInt();

	void PrintElement(const std::string& str);

	std::string m_expression;
	size_t m_index = 0;
	size_t m_from = 0;
	size_t m_to = 1;
	size_t m_state = 2;

	bool m_isBracket = false;
	bool m_isOrTheLastInBracket = false;
	size_t m_start = 0;
	size_t m_end = 0;
};