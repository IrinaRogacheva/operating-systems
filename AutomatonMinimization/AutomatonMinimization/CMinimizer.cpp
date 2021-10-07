#include "CMinimizer.h"
#include <set>
#include <iostream>

CMinimizer::CMinimizer()
	:m_machineInfo({ 0, 0, 0 })
{
}

void CMinimizer::MinimizeMachine()
{
	FindFirstEquivalenceClass();

	do
	{
		m_previousSplittingByEquivalenceClasses = m_splittingByEquivalenceClasses;
		std::vector <std::vector<int>> newTransitions = GetNewTransitions();
		FindNextEquivalenceClass(newTransitions);

	} while (m_previousSplittingByEquivalenceClasses != m_splittingByEquivalenceClasses);

	RemoveEquivalentStates();
	ReplaceTransitions();
}

void CMinimizer::RemoveEquivalentStates()
{
}

void CMinimizer::ReplaceTransitions()
{
	for (size_t i = 0; i < m_transitions.size(); i++)
	{
		for (size_t j = 0; j < m_transitions[i].size(); j++)
		{
			if (!m_isThereZeroState)
			{
				m_transitions[i][j] = m_splittingByEquivalenceClasses[m_transitions[i][j] - 1];
			}
			else
			{
				m_transitions[i][j] = m_splittingByEquivalenceClasses[m_transitions[i][j]];
			}
		}
	}
}

void CMinimizer::SetTransitions(const std::vector<std::vector<int>> transitions)
{
	m_transitions = transitions;
}

void CMinimizer::SetIsThereZeroState(const bool isThereZeroState)
{
	m_isThereZeroState = isThereZeroState;
}

void CMinimizer::SetMachineInfo(const SMachineInfo SMachineInfo)
{
	m_machineInfo = SMachineInfo;
}

bool CMinimizer::GetIsThereZeroState()
{
	return m_isThereZeroState;
}

std::vector<std::vector<int>> CMinimizer::GetTransitions()
{
	return m_transitions;
}

void CMinimizer::FindFirstEquivalenceClass()
{
}

void CMinimizer::FindNextEquivalenceClass(const std::vector <std::vector<int>> newTransitions)
{
	int numberOfNewEquivalenceClass = 0;
	m_splittingByEquivalenceClasses[0] = numberOfNewEquivalenceClass;
	bool isFound;
	for (size_t i = 1; i < newTransitions.size(); i++)
	{
		isFound = false;
		for (size_t j = 0; j < i; j++)
		{
			if (newTransitions[j] == newTransitions[i] && m_previousSplittingByEquivalenceClasses[j] == m_previousSplittingByEquivalenceClasses[i])
			{
				m_splittingByEquivalenceClasses[i] = m_splittingByEquivalenceClasses[j];
				isFound = true;
				break;
			}
		}

		if (!isFound)
		{
			numberOfNewEquivalenceClass++;
			m_splittingByEquivalenceClasses[i] = numberOfNewEquivalenceClass;
		}
	}
}

std::vector <std::vector<int>> CMinimizer::GetNewTransitions()
{
	std::vector <std::vector<int>> newTransitions(m_machineInfo.numberOfStates);
	for (size_t i = 0; i < m_transitions.size(); i++)
	{
		for (size_t j = 0; j < m_transitions[i].size(); j++)
		{
			if (!m_isThereZeroState)
			{
				newTransitions[i].push_back(m_splittingByEquivalenceClasses[m_transitions[i][j] - 1]);
			}
			else
			{
				newTransitions[i].push_back(m_splittingByEquivalenceClasses[m_transitions[i][j]]);
			}
		}
	}

	return newTransitions;
}

