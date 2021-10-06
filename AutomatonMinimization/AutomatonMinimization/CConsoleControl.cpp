#include "CConsoleControl.h"
#include <exception>
#include <sstream>
#include <algorithm>

CConsoleControl::CConsoleControl(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_machineInfo({0, 0, 0})
	, m_actionMap(
		{
			{ "Ml", std::bind(&CConsoleControl::MinimizeMealyMachine, this) },
			{ "Mr", std::bind(&CConsoleControl::MinimizeMooreMachine, this) }
		})
{
}

void CConsoleControl::HandleCommand()
{
	std::string consoleLine;
	getline(m_input, consoleLine);

	auto it = m_actionMap.find(consoleLine);

	GetMachineInfo();

	return it->second();
}

void CConsoleControl::MinimizeMealyMachine()
{
	ReadMealyAutomaton();
	m_mealyMinimizer.MinimizeMachine();
	WriteMinimizedMealyAutomaton(m_mealyMinimizer.GetIsThereZeroState());
}

void CConsoleControl::WriteMinimizedMealyAutomaton(const bool isThereZeroState)
{
	std::vector <std::vector<int>> transitions = m_mealyMinimizer.GetTransitions();
	std::vector <std::vector<int>> outputs = m_mealyMinimizer.GetOutputs();

	std::vector<std::vector<std::string>> result(transitions[0].size(), std::vector<std::string>(transitions.size()));
	for (size_t i = 0; i < transitions[0].size(); i++)
	{
		for (size_t j = 0; j < transitions.size(); j++) 
		{
			result[i][j] = std::to_string(transitions[j][i]).append("/y").append(std::to_string(outputs[j][i]));
		}
	}

	for (size_t i = 0; i < result.size(); i++)
	{
		for (size_t j = 0; j < result[i].size(); j++)
		{
			m_output << "S" << result[i][j] << " ";
		}
		m_output << "\n";
	}
}

void CConsoleControl::WriteMinimizedMooreAutomaton(const bool isThereZeroState)
{
	std::vector <std::vector<int>> transitions = m_mooreMinimizer.GetTransitions();
	std::vector<int> outputs = m_mooreMinimizer.GetOutputs();

	for (size_t i = 0; i < outputs.size(); i++)
	{
		m_output << "y" << outputs[i] << " ";
	}
	m_output << "\n";

	std::vector<std::vector<int>> result(transitions[0].size(), std::vector<int>(transitions.size()));
	for (size_t i = 0; i < transitions[0].size(); i++)
	{
		for (size_t j = 0; j < transitions.size(); j++)
		{
			result[i][j] = transitions[j][i];
		}
	}

	for (size_t i = 0; i < result.size(); i++)
	{
		for (size_t j = 0; j < result[i].size(); j++)
		{
			m_output << "S" << result[i][j] << " ";
		}
		m_output << "\n";
	}
}

void CConsoleControl::MinimizeMooreMachine()
{
	ReadOutputCharactersForMooreAutomaton();
	ReadMooreAutomaton();
	m_mooreMinimizer.MinimizeMachine();
	WriteMinimizedMooreAutomaton(m_mooreMinimizer.GetIsThereZeroState());
}

int CConsoleControl::ReadInt()
{
	std::string str;
	getline(m_input, str);
	return  std::stoi(str);
}

void CConsoleControl::GetMachineInfo()
{
	m_machineInfo.numberOfStates = ReadInt();
	m_machineInfo.numberOfInputCharacters = ReadInt();
	m_machineInfo.numberOfOutputCharacters = ReadInt();

	m_mealyMinimizer.SetMachineInfo(m_machineInfo);
	m_mooreMinimizer.SetMachineInfo(m_machineInfo);
}

void CConsoleControl::ReadMealyAutomaton()
{
	std::vector <std::vector<int>> transitions(m_machineInfo.numberOfStates);
	std::vector <std::vector<int>> outputs(m_machineInfo.numberOfStates);

	std::string str;
	for (size_t i = 0; i < m_machineInfo.numberOfInputCharacters; i++)
	{
		str = GetLineWithoutInputCharacter();
		std::stringstream iss(str);
		
		for (size_t j = 0; j < m_machineInfo.numberOfStates; j++)
		{
			getline(iss, str, '/');
			str.erase(0, str.find_first_of("1234567890"));
			if (str == "0")
			{
				m_mealyMinimizer.SetIsThereZeroState(true);
			}
			transitions[j].push_back(std::stoi(str));
			
			getline(iss, str, ' ');
			str.erase(0, str.find_first_of("1234567890"));
			outputs[j].push_back(std::stoi(str));
		}
	}

	m_mealyMinimizer.SetTransitions(transitions);
	m_mealyMinimizer.SetOutputs(outputs);

}

std::string CConsoleControl::GetLineWithoutInputCharacter()
{
	std::string str;
	getline(m_input, str);
	if (str.find(":") != std::string::npos)
	{
		str.erase(0, str.find(" ") + 1);
	}
	return str;
}

void CConsoleControl::ReadOutputCharactersForMooreAutomaton()
{
	std::vector <int> outputs;
	std::string str;
	getline(m_input, str);
	std::stringstream iss(str);
	for (size_t i = 0; i < m_machineInfo.numberOfStates; i++)
	{
		getline(iss, str, ' ');
		str.erase(0, str.find_first_of("1234567890"));
		outputs.push_back(std::stoi(str));
	}

	m_mooreMinimizer.SetOutputs(outputs);
}

void CConsoleControl::ReadMooreAutomaton()
{
	std::vector <std::vector<int>> transitions(m_machineInfo.numberOfStates);

	std::string str;
	for (size_t i = 0; i < m_machineInfo.numberOfInputCharacters; i++)
	{
		str = GetLineWithoutInputCharacter();
		std::stringstream iss(str);

		for (size_t j = 0; j < m_machineInfo.numberOfStates; j++)
		{
			getline(iss, str, ' ');
			str.erase(0, str.find_first_of("1234567890"));
			if (str == "0")
			{
				m_mooreMinimizer.SetIsThereZeroState(true);
			}
			transitions[j].push_back(std::stoi(str));
		}
	}

	m_mooreMinimizer.SetTransitions(transitions);
}

