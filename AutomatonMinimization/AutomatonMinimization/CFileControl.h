#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "CMealyMinimizer.h"
#include "CMooreMinimizer.h"

class CFileControl
{
public:
	CFileControl(std::istream& input, std::ostream& output);
	void HandleCommand();

private:
	void MinimizeMealyMachine();
	void MinimizeMooreMachine();
	int ReadInt();
	void ReadMealyAutomaton();
	void ReadMooreAutomaton();
	void GetMachineInfo();
	std::string GetLineWithoutInputCharacter();
	void ReadOutputCharactersForMooreAutomaton();
	void WriteMinimizedMealyAutomaton(const bool isThereZeroState);
	void WriteMinimizedMooreAutomaton(const bool isThereZeroState);

	std::istream& m_input;
	std::ostream& m_output;

	SMachineInfo m_machineInfo;
	CMealyMinimizer m_mealyMinimizer;
	CMooreMinimizer m_mooreMinimizer;

	typedef std::function<void()> Handler;
	typedef std::map<std::string, Handler> ActionMap;
	const ActionMap m_actionMap;
};