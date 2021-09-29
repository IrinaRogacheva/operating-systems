#include "CConsoleControl.h"
#include <exception>
#include <sstream>
#include <algorithm>

CConsoleControl::CConsoleControl(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
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
	if (it == m_actionMap.end())
	{
		throw std::invalid_argument("Введите строку \"Ml\" или \"Mr\"");
	}
	
	try
	{
		GetQuantitativeParamsOfMachine();
	}
	catch (std::exception&)
	{
		throw;
	}

	return it->second();
}

void CConsoleControl::MinimizeMealyMachine()
{
	ReadMealyAutomaton();
	std::vector<std::vector<int>> infoAboutEquivalenceStates = m_mealyMinimizer.MinimizeMealyMachine();
	WriteInfoAboutEquivalenceStates(infoAboutEquivalenceStates, m_mealyMinimizer.GetIsThereZeroState());
	std::vector <std::vector<int>> transitionMap = m_mealyMinimizer.GetTransitionMap();
	std::vector <std::string> outputMap = m_mealyMinimizer.GetOutputMap();
	m_output << "переходы:\n";
	for (std::vector<int> vectorOfStateNumber : transitionMap)
	{
		for (int stateNumber : vectorOfStateNumber)
		{
			m_output << stateNumber << " ";
		}
		m_output << "\n";
	}

	m_output << "выходы:\n";
	for (std::string str : outputMap)
	{
		m_output << str << "\n";
	}
}

void CConsoleControl::WriteInfoAboutEquivalenceStates(std::vector<std::vector<int>> infoAboutEquivalenceStates, bool isThereZeroState)
{
	if (infoAboutEquivalenceStates.size() < m_numberOfStates)
	{
		m_output << "Найдены следующие эквивалентные состояния: ";
		for (std::vector<int> equivalenceStates : infoAboutEquivalenceStates)
		{
			//if(equivalenceStates.size() > 1)
			{
				m_output << " { ";
				for (int equivalenceState : equivalenceStates)
				{
					if (!isThereZeroState)
					{
						m_output << equivalenceState + 1 << " ";
					}
				}
				m_output << "} ";
			}
		}
		m_output << "\n";
	}
	else
	{ 
		m_output << "Автомат уже минимизирован";
	}
}

void CConsoleControl::MinimizeMooreMachine()
{
	ReadOutputCharactersForMooreAutomaton();
	ReadMooreAutomaton();
	m_mooreMinimizer.MinimizeMooreMachine();
}

int CConsoleControl::ReadPositiveInt()
{
	std::string str;
	getline(m_input, str);
	std::istringstream strm(str);

	int x;
	strm >> x;
	if (strm.fail() || x <= 0)
	{
		throw std::invalid_argument("Число должно быть целым и больше 0");
	}
	return  x;
}

void CConsoleControl::GetQuantitativeParamsOfMachine()
{
	try
	{
		m_output << "Введите количество состояний\n>";
		m_numberOfStates = ReadPositiveInt();
		m_output << "Введите количество входных символов\n>";
		m_numberOfInputCharacters = ReadPositiveInt();
		m_output << "Введите количество выходных символов\n>";
		m_numberOfOutputCharacters = ReadPositiveInt();
	}
	catch (std::exception&)
	{
		throw;
	}
}

void CConsoleControl::ReadMealyAutomaton()
{
	std::vector <std::vector<int>> transitionMap;
	std::vector <std::string> outputMap;
	transitionMap.resize(m_numberOfStates);
	outputMap.resize(m_numberOfStates);

	std::string str;
	for (int i = 0; i < m_numberOfInputCharacters; i++)
	{
		m_output << "Введите строку таблицы\n>";

		str = GetLineWithoutInputCharacter();
		std::stringstream iss(str);
		
		for (int j = 0; j < m_numberOfStates; j++)
		{
			getline(iss, str, '/');
			str.erase(0, str.find_first_of("1234567890"));
			if (str == "0")
			{
				m_mealyMinimizer.SetIsThereZeroState(true);
			}
			transitionMap[j].push_back(std::stoi(str));
			
			getline(iss, str, ' ');
			transform(str.begin(), str.end(), str.begin(), tolower);
			outputMap[j].append(str);
		}
	}

	m_mealyMinimizer.SetTransitionMap(transitionMap);
	m_mealyMinimizer.SetOutputMap(outputMap);

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
	std::vector <int> outputMap;
	m_output << "Введите строку выходных сигналов\n>";
	std::string str;
	getline(m_input, str);
	std::stringstream iss(str);
	for (int i = 0; i < m_numberOfStates; i++)
	{
		getline(iss, str, ' ');
		str.erase(0, str.find_first_of("1234567890"));
		outputMap.push_back(std::stoi(str));
	}

	m_mooreMinimizer.SetOutputMap(outputMap);
}

void CConsoleControl::ReadMooreAutomaton()
{
	std::vector <std::vector<int>> transitionMap;
	transitionMap.resize(m_numberOfStates);

	std::string str;
	for (int i = 0; i < m_numberOfInputCharacters; i++)
	{
		m_output << "Введите строку таблицы\n>";

		str = GetLineWithoutInputCharacter();
		std::stringstream iss(str);

		for (int j = 0; j < m_numberOfStates; j++)
		{
			getline(iss, str, ' ');
			str.erase(0, str.find_first_of("1234567890"));
			transitionMap[j].push_back(std::stoi(str));
		}
	}

	m_mooreMinimizer.SetTransitionMap(transitionMap);
}

