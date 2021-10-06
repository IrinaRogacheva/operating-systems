#pragma once
#include <string>
#include <vector>
#include "SMachineInfo.h"

class CMealyMinimizer
{
public:
	CMealyMinimizer();
	void MinimizeMachine();
	void SetTransitions(const std::vector <std::vector<int>> transitions);
	void SetOutputs(const std::vector <std::vector<int>> outputs);
	void SetIsThereZeroState(const bool isThereZeroState);
	void SetMachineInfo(const SMachineInfo SMachineInfo);
	bool GetIsThereZeroState();
	std::vector <std::vector<int>> GetTransitions();
	std::vector <std::vector<int>> GetOutputs();
	void FindFirstEquivalenceClass();
private:
	std::vector <std::vector<int>> GetNewTransitions();
	void FindNextEquivalenceClass(const std::vector <std::vector<int>> newTransitions);
	void RemoveEquivalentStates();
	void ReplaceTransitions();

	std::vector <std::vector<int>> m_transitions;
	std::vector <std::vector<int>> m_outputs;

	std::vector<int> m_splittingByEquivalenceClasses;
	std::vector<int> m_previousSplittingByEquivalenceClasses;

	SMachineInfo m_machineInfo;

	bool m_isThereZeroState = false;
};
