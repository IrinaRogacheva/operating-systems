#include "CMooreMinimizer.h"
#include <set>

CMooreMinimizer::CMooreMinimizer()
{
}

void CMooreMinimizer::MinimizeMooreMachine()
{
	
}

void CMooreMinimizer::SetTransitionMap(std::vector<std::vector<int>> transitionMap)
{
	m_transitionMap = transitionMap;
}

void CMooreMinimizer::SetOutputMap(std::vector<int> outputMap)
{
	m_outputMap = outputMap;
}
