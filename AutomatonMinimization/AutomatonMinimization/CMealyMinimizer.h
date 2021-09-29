#pragma once
#include <string>
#include <vector>

class CMealyMinimizer
{
public:
	CMealyMinimizer();
	std::vector<std::vector<int>> MinimizeMealyMachine();
	void SetTransitionMap(std::vector <std::vector<int>> transitionMap);
	void SetOutputMap(std::vector <std::string> outputMap);
	void SetIsThereZeroState(bool isThereZeroState);
	bool GetIsThereZeroState();
	std::vector <std::vector<int>> GetTransitionMap();
	std::vector <std::string> GetOutputMap();
private:
	void FindFirstEquivalenceClasses();
	void FindNextPartition(int numberOfEquivalenceClass);
	std::vector <std::vector<int>> GetNewTransitions(int numberOfEquivalenceClass);
	void FindNextEquivalenceClass(int numberOfEquivalenceClass, std::vector <std::vector<int>> newTransitions);
	void GetMinimizedMachine();

	std::vector <std::vector<int>>  GetInfoAboutEquivalenceStates();

	std::vector <std::vector<int>> m_transitionMap;
	std::vector <std::string> m_outputMap;

	std::vector <int> m_equivalenceClasses;
	std::vector <std::vector<int>> m_equivalenceClassesToStates;

	bool m_isThereZeroState = false;
};
