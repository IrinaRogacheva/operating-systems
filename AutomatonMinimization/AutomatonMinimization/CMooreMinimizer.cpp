#include "CMooreMinimizer.h"
#include <set>
#include <iostream>

CMooreMinimizer::CMooreMinimizer()
{
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

void CMooreMinimizer::SetOutputs(const std::vector<int> outputs)
{
	m_outputs = outputs;
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
