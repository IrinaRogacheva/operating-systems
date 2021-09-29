#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "CMealyMinimizer.h"
#include "CMooreMinimizer.h"

class CConsoleControl
{
public:
	CConsoleControl(std::istream& input, std::ostream& output);
	void HandleCommand();

private:
	void MinimizeMealyMachine();
	void MinimizeMooreMachine();
	int ReadPositiveInt();
	void ReadMealyAutomaton();
	void ReadMooreAutomaton();
	void GetQuantitativeParamsOfMachine();
	std::string GetLineWithoutInputCharacter();
	void ReadOutputCharactersForMooreAutomaton();
	void WriteInfoAboutEquivalenceStates(std::vector<std::vector<int>> infoAboutEquivalenceStates, bool isThereZeroState);

	std::istream& m_input;
	std::ostream& m_output;

	int m_numberOfStates;
	int m_numberOfInputCharacters;
	int m_numberOfOutputCharacters;

	CMealyMinimizer m_mealyMinimizer;
	CMooreMinimizer m_mooreMinimizer;

	typedef std::function<void()> Handler;
	typedef std::map<std::string, Handler> ActionMap;
	const ActionMap m_actionMap;
};