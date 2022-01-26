#include "Converter.h"
#include <exception>
#include <sstream>
#include <algorithm>
#include <set>
#include <iomanip>

CConverter::CConverter(const std::string& expression)
	: m_expression(expression)
{
}

CAutomaton CConverter::ConvertExpressionToAutomaton()
{
	CAutomaton::NondeterministicAutomaton automaton;

	bool isContinue = true;
	while (isContinue)
	{
		std::cout << "loop\n";
		ProcessExpression(automaton);
		if (m_index >= m_expression.size())
		{
			isContinue = false;
		}
	}
	CAutomaton automatonObject(automaton);
	return automatonObject;
}

void CConverter::ProcessExpression(CAutomaton::NondeterministicAutomaton& automaton)
{
	if (m_expression[m_index] == '(')
	{
		ProcessBracket(automaton);
	}
	else if (m_expression[m_index] == '|')
	{
		ProcessOr(automaton);
	}
	else if (m_expression[m_index] == '*' || m_expression[m_index] == '+')
	{
		m_index--;
		if (m_from == m_to)
		{
			m_to = m_state + 1;
		}
		if (m_expression[m_index + 1] == '*')
		{
			ProcessAsterisk(automaton, { m_expression[m_index] });
		}
		else
		{
			ProcessPlusSign(automaton);
		}
		m_state++;
		if (m_expression[m_index + 2] != '|')
		{
			m_from = m_to;
			m_to = m_state;
		}
		
		if (CheckIsNextOperationRecursive())
		{
			m_state++;
		}

		m_index += 2;
	}
	else
	{
		ProcessSimpleTransition(automaton);
	}
}

void CConverter::ProcessAsterisk(CAutomaton::NondeterministicAutomaton& automaton, std::optional<char> action)
{
	std::string actionStr;
	if (action)
	{
		actionStr = { *action };
	}
	automaton.emplace(std::make_pair(m_from, std::nullopt), m_state);
	if (action)
	{
		automaton.emplace(std::make_pair(m_state, actionStr), m_state);
	}
	automaton.emplace(std::make_pair(m_state, std::nullopt), m_to);
}

void CConverter::ProcessPlusSign(CAutomaton::NondeterministicAutomaton& automaton)
{
	std::string action = { m_expression[m_index] };
	automaton.emplace(std::make_pair(m_from, action), m_state);
	automaton.emplace(std::make_pair(m_state, action), m_state);
	automaton.emplace(std::make_pair(m_state, std::nullopt), m_to);
}

void CConverter::ProcessOr(CAutomaton::NondeterministicAutomaton& automaton)
{
	std::string action = { m_expression[m_index - 1] };
	m_index++;
	if (m_expression[m_index + 1] == '*' || m_expression[m_index + 1] == '+')
	{
		if (m_expression[m_index + 1] == '*')
		{
			ProcessAsterisk(automaton, m_expression[m_index]);
		}
		else
		{
			ProcessPlusSign(automaton);
		}
		m_state++;
		m_index += 2;
	}
	// обработка скобочки
	else
	{
		std::string act = { m_expression[m_index] };
		automaton.emplace(std::make_pair(m_from, act), m_to);
		
		m_index++;
	}
	if (action != "*" && action != "|" && action != "+" && action != "(" && action != ")")// скобочки под вопросом
	{
		automaton.emplace(std::make_pair(m_from, action), m_to);
	}
	if (m_expression[m_index] != '|')
	{
		m_from = m_to;
		m_to = m_state;
	}
	else
	{
		m_index++;
	}
	if (m_isOrTheLastInBracket)
	{
		automaton.emplace(std::make_pair(m_to, std::nullopt), m_start);
	}
}

void CConverter::ProcessSimpleTransition(CAutomaton::NondeterministicAutomaton& automaton)
{
	std::string action = { m_expression[m_index] };
	if (m_expression[m_index + 1] != '*' && m_expression[m_index + 1] != '+' && m_expression[m_index + 1] != '|')
	{
		if (m_expression[m_index + 1] != ')')
		{
			automaton.emplace(std::make_pair(m_from, action), m_to);
		}
		else
		{
			automaton.emplace(std::make_pair(m_from, action), m_start);
		}
		m_from = m_to;
		if (m_isBracket)
		{
			m_state++;
			m_to = m_state;
		}
		else
		{
			m_to = m_state;
			m_state++;
		}
	}
	m_index++;
}

void CConverter::ProcessBracket(CAutomaton::NondeterministicAutomaton& automaton)
{
	m_index++;

	std::string::size_type closingBracket = m_expression.find(')');
	if (m_expression[closingBracket + 1] == '*')
	{
		ProcessAsterisk(automaton);
		m_start = m_state;
		m_from = m_state;
		m_state++;
		m_end = m_to;
		m_to = m_state;
	}
	m_isBracket = true;
	CheckIsOrTheLastOperationInBracket(closingBracket);
	while (m_expression[m_index] != ')')
	{
		ProcessExpression(automaton);
	}
	if (m_expression[closingBracket + 1] == '*')
	{
		m_index += 2;
	}
	m_isBracket = false;
	m_isOrTheLastInBracket = false;
	m_from = m_end;
	m_to = m_state;
	m_state++;
}

void CConverter::CheckIsOrTheLastOperationInBracket(size_t posOfClosingBracket)
{
	m_isOrTheLastInBracket = true;
	if (m_expression[posOfClosingBracket - 1] == '*' || m_expression[posOfClosingBracket - 1] == '+')
	{
		m_isOrTheLastInBracket = false;
		return;
	}
	if (m_expression[posOfClosingBracket - 2] == '|' || m_expression[posOfClosingBracket - 1] == ')')
	{
		return;
	}
}

bool CConverter::CheckIsNextOperationRecursive()
{
	if (m_index + 3 > m_expression.size())
	{
		return false;
	}
	if (m_expression[m_index + 3] == '*' || m_expression[m_index + 3] == '+')
	{
		return true;
	}
	/*if (m_expression[m_index + 3] == '(')
	{
		size_t posOfClosingBracket = m_expression.find(")", m_index + 3);
		if (m_expression[posOfClosingBracket + 1] == '*' || m_expression[posOfClosingBracket + 1] == '+')
		{
			return true;
		}
	}*/
	return false;
}
