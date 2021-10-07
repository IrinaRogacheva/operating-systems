#pragma once
#include <string>
#include <vector>
#include "SMachineInfo.h"

class CMinimizer
{
public:
	CMinimizer();
	void MinimizeMachine();
	void SetTransitions(const std::vector <std::vector<int>> transitions);
	void SetIsThereZeroState(const bool isThereZeroState);
	void SetMachineInfo(const SMachineInfo SMachineInfo);
	bool GetIsThereZeroState();
	virtual std::vector <std::vector<int>> GetTransitions();
protected:
	virtual void FindFirstEquivalenceClass();
	virtual void RemoveEquivalentStates();
	std::vector <std::vector<int>> GetNewTransitions();
	void FindNextEquivalenceClass(const std::vector <std::vector<int>> newTransitions);
	void ReplaceTransitions();

	std::vector <std::vector<int>> m_transitions;
	std::vector<int> m_splittingByEquivalenceClasses;
	std::vector<int> m_previousSplittingByEquivalenceClasses;

	SMachineInfo m_machineInfo;

	bool m_isThereZeroState = false;
};
