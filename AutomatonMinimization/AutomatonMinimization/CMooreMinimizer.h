#pragma once
#include <string>
#include <vector>
#include "CMinimizer.h"

class CMooreMinimizer: public CMinimizer
{
public:
	CMooreMinimizer();
	void SetOutputs(const std::vector<int> outputs);
	std::vector<int> GetOutputs();
private:
	void FindFirstEquivalenceClass() override;
	void RemoveEquivalentStates() override;
	std::vector<int> m_outputs;
};
