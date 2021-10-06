#include "CMooreMinimizer.h"
#include <set>
#include <iostream>

CMooreMinimizer::CMooreMinimizer()
	:m_machineInfo({ 0, 0, 0 })
{
}

void CMooreMinimizer::MinimizeMachine()
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

void CMooreMinimizer::RemoveEquivalentStates()
{
	std::set<int> uniqueClasses;
	std::vector <std::vector<int>> newTransitions;
	std::vector<int> newOutputs;

	for (size_t i = 0; i < m_transitions.size(); i++)
	{
		if (!uniqueClasses.count(m_splittingByEquivalenceClasses[i]))
		{
			newTransitions.push_back(m_transitions[i]);
			newOutputs.push_back(m_outputs[i]);
		}
		uniqueClasses.insert(m_splittingByEquivalenceClasses[i]);
	}

	m_transitions = newTransitions;
	m_outputs = newOutputs;
}

void CMooreMinimizer::ReplaceTransitions()
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

void CMooreMinimizer::SetTransitions(const std::vector<std::vector<int>> transitions)
{
	m_transitions = transitions;
}

void CMooreMinimizer::SetOutputs(const std::vector<int> outputs)
{
	m_outputs = outputs;
}

void CMooreMinimizer::SetIsThereZeroState(const bool isThereZeroState)
{
	m_isThereZeroState = isThereZeroState;
}

void CMooreMinimizer::SetMachineInfo(const SMachineInfo SMachineInfo)
{
	m_machineInfo = SMachineInfo;
}

bool CMooreMinimizer::GetIsThereZeroState()
{
	return m_isThereZeroState;
}

std::vector<std::vector<int>> CMooreMinimizer::GetTransitions()
{
	return m_transitions;
}

std::vector<int> CMooreMinimizer::GetOutputs()
{
	return m_outputs;
}

void CMooreMinimizer::FindFirstEquivalenceClass()
{
	std::set<int> uniqueOutputs(m_outputs.begin(), m_outputs.end());

	std::set<int>::iterator it;
	for (size_t i = 0; i < m_outputs.size(); i++)
	{
		it = uniqueOutputs.find(m_outputs[i]);
		if (it != uniqueOutputs.end())
		{
			m_splittingByEquivalenceClasses.push_back(std::distance(uniqueOutputs.begin(), it));
		}
	}

}

void CMooreMinimizer::FindNextEquivalenceClass(const std::vector <std::vector<int>> newTransitions)
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

std::vector <std::vector<int>> CMooreMinimizer::GetNewTransitions()
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

