#include "TableRunner.h"
#include <stack>

CTableRunner::CTableRunner(std::vector<Row> table)
	: m_table(table)
{
}

bool CTableRunner::Run(const std::string& expression)
{
	std::stack<int> pointersStack;
	std::vector<std::string> v;
	std::string str;
	size_t numberOfRow = 0;
	Row row = m_table[numberOfRow];
	size_t i = 0;
	while (!row.isEnd)
	{
		row = m_table[numberOfRow];
		
		v = row.guidingSymbols;
		str = { expression[i] };
		if (std::find(row.guidingSymbols.begin(), row.guidingSymbols.end(), str) == row.guidingSymbols.end() && row.error)
		{
			return false;
		}

		if (row.shift)
		{
			i++;
		}

		if (row.isInsertInStack)
		{
			pointersStack.push(numberOfRow + 1);
		}

		if (!row.error)
		{
			numberOfRow++;
			break;
		}

		if (row.pointer == 0)
		{
			numberOfRow = pointersStack.top();
			pointersStack.pop();
		}
		else if (row.pointer != -1)
		{
			numberOfRow = row.pointer - 1;
		}
	}
	return true;
}
