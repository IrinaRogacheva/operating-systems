#pragma once
#include <string>
#include <vector>

struct Row
{
	std::string symbol;
	std::vector<std::string> guidingSymbols;
	bool shift;
	bool error;
	size_t pointer;
	bool isInsertInStack;
	bool isEnd;
};