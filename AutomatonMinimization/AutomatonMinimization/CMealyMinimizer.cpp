#include "CMealyMinimizer.h"
#include <set>
#include <iostream>

CMealyMinimizer::CMealyMinimizer()
{
}

std::vector<std::vector<int>> CMealyMinimizer::MinimizeMealyMachine()
{
	FindFirstEquivalenceClasses();

	int i = 0;
	do
	{
		FindNextPartition(i);
		i++;
	} while (m_equivalenceClasses[m_equivalenceClasses.size() - 1] > m_equivalenceClasses[m_equivalenceClasses.size() - 2]);

	GetMinimizedMachine();

	return GetInfoAboutEquivalenceStates();
}

std::vector<std::vector<int>> CMealyMinimizer::GetInfoAboutEquivalenceStates()
{
	std::vector<std::vector<int>> infoAboutEquivalenceStates;
	int numberOfEquivalenceClasses = m_equivalenceClasses[m_equivalenceClasses.size() - 1] + 1;
	infoAboutEquivalenceStates.resize(numberOfEquivalenceClasses);
	for (int i = 0; i < m_equivalenceClassesToStates[m_equivalenceClassesToStates.size() - 1].size(); i++)//количество состояний
	{
		for (int j = 0; j < numberOfEquivalenceClasses; j++)
		{
			if (m_equivalenceClassesToStates[m_equivalenceClassesToStates.size()-1][i] == j)
			{
				if (!m_isThereZeroState)
				{
					infoAboutEquivalenceStates[j].push_back(i);
				}
			}
		}
	}
	return infoAboutEquivalenceStates;
}

void CMealyMinimizer::GetMinimizedMachine()
{
	std::set<int> uniqueClasses;
	for (int i = 0; i < m_transitionMap.size(); i++)
	{
		if (uniqueClasses.count(m_equivalenceClassesToStates[m_equivalenceClassesToStates.size() - 1][i]))
		{
			m_transitionMap.erase(m_transitionMap.begin() + i);
		}
		uniqueClasses.insert(m_equivalenceClassesToStates[m_equivalenceClassesToStates.size() - 1][i]);
	}
}

void CMealyMinimizer::SetTransitionMap(std::vector<std::vector<int>> transitionMap)
{
	m_transitionMap = transitionMap;
}

void CMealyMinimizer::SetOutputMap(std::vector<std::string> outputMap)
{
	m_outputMap = outputMap;
}

void CMealyMinimizer::SetIsThereZeroState(bool isThereZeroState)
{
	m_isThereZeroState = isThereZeroState;
}

bool CMealyMinimizer::GetIsThereZeroState()
{
	return m_isThereZeroState;
}

std::vector<std::vector<int>> CMealyMinimizer::GetTransitionMap()
{
	return m_transitionMap;
}

std::vector<std::string> CMealyMinimizer::GetOutputMap()
{
	return m_outputMap;
}

void CMealyMinimizer::FindFirstEquivalenceClasses()
{
	std::set<std::string> uniqueOutputs(m_outputMap.begin(), m_outputMap.end());
	m_equivalenceClasses.push_back(uniqueOutputs.size());

	std::vector<int> equivalenceClasses;

	std::set<std::string>::iterator it;
	for (int i = 0; i < m_outputMap.size(); i++)
	{
		it = uniqueOutputs.find(m_outputMap[i]);
		if (it != uniqueOutputs.end())
		{
			equivalenceClasses.push_back(std::distance(uniqueOutputs.begin(), it));
		}
	}
	m_equivalenceClassesToStates.push_back(equivalenceClasses);
}

void CMealyMinimizer::FindNextEquivalenceClass(int numberOfEquivalenceClass, std::vector <std::vector<int>> newTransitions)
{
	std::vector<int> equivalenceClasses;
	equivalenceClasses.resize(newTransitions.size());
	int numberOfNewEquivalenceClass = 0;
	equivalenceClasses[0] = numberOfNewEquivalenceClass;
	
	for (int i = 1; i < newTransitions.size(); i++)
	{
		bool isFound = false;
		for (int j = 0; j < i; j++)
		{
			if (newTransitions[j] == newTransitions[i])
			{
				equivalenceClasses[i] = equivalenceClasses[j];
				isFound = true;
				break;
			}
		}

		if (!isFound)
		{
			numberOfNewEquivalenceClass++;
			equivalenceClasses[i] = numberOfNewEquivalenceClass;
		}
	}
	m_equivalenceClassesToStates.push_back(equivalenceClasses);
	m_equivalenceClasses.push_back(numberOfNewEquivalenceClass);
}

void CMealyMinimizer::FindNextPartition(int numberOfEquivalenceClass)//nextEquivalenceClass
{
	std::vector <std::vector<int>> newTransitions = GetNewTransitions(numberOfEquivalenceClass);
	FindNextEquivalenceClass(numberOfEquivalenceClass, newTransitions);
}

std::vector <std::vector<int>> CMealyMinimizer::GetNewTransitions(int numberOfEquivalenceClass)
{
	std::vector <std::vector<int>> newTransitions;
	newTransitions.resize(m_transitionMap.size());
	for (int i = 0; i < m_transitionMap.size(); i++)
	{
		for (int j = 0; j < m_transitionMap[i].size(); j++)
		{
			if (!m_isThereZeroState)
			{
				newTransitions[i].push_back(m_equivalenceClassesToStates[numberOfEquivalenceClass][m_transitionMap[i][j] - 1]);
			}
		}
	}
	return newTransitions;
}

