#pragma once
#include <string>
#include <vector>

class CMooreMinimizer
{
public:
	CMooreMinimizer();
	void MinimizeMooreMachine();
	void SetTransitionMap(std::vector <std::vector<int>> transitionMap);
	void SetOutputMap(std::vector <int> outputMap);
private:
	std::vector <std::vector<int>> m_transitionMap;
	std::vector <int> m_outputMap;
};
