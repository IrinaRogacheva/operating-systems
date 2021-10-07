#pragma once
#include <string>
#include <vector>
#include "CMinimizer.h"

class CMealyMinimizer: public CMinimizer
{
public:
	CMealyMinimizer();
	void SetOutputs(const std::vector <std::vector<int>> outputs);
	std::vector<std::vector<int>> GetOutputs();
private:
	void FindFirstEquivalenceClass() override;
	void RemoveEquivalentStates() override;
	std::vector <std::vector<int>> m_outputs;
};
