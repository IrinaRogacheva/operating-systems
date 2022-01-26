#include "Automaton.h"

CAutomaton::CAutomaton(NondeterministicAutomaton automaton/*, std::set<std::string> actions*/)
	: m_automaton(automaton)
	//, m_actions(actions)
{
};

CAutomaton::NondeterministicAutomaton CAutomaton::GetAutomaton() const
{
	return m_automaton;
}

std::set<std::string> CAutomaton::GetActions() const
{
	return m_actions;
}
