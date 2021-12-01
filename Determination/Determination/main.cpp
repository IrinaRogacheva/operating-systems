#include <iostream>
#include <fstream>
#include "FileControl.h"
#include "Grammar.h"
#include "Determinator.h"

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	CFileControl fileControl(input, output);

	CGrammar grammar = fileControl.ReadGrammar();

	CDeterminator determinator(grammar);
	determinator.Determinate();
}
