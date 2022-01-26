#include <iostream>
#include <fstream>
#include "Converter.h"
#include "Automaton.h"
//#include "Determinator.h"

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	std::string expression;
	getline(input, expression);

	CConverter converter(expression);

	CAutomaton nondeterministicAutomaton = converter.ConvertExpressionToAutomaton();

	for (auto item : nondeterministicAutomaton.GetAutomaton())
	{

		if (item.first.second)
		{
			output << item.first.first << " " << *item.first.second << " " << item.second << std::endl;
		}
		else
		{
			output << item.first.first << " " << 'e' << " " << item.second << std::endl;
		}
	}
	//CDeterminator determinator(grammar);
	//fileControl.WriteGrammar(determinator.Determinate(), grammar.GetActions());
}
