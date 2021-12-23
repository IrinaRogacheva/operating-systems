#include "FileControl.h"
#include <sstream>

CFileControl::CFileControl(std::istream& tableInput, std::istream& input, std::ostream& output)
	: m_input(input)
	, m_tableInput(tableInput)
	, m_output(output)
{
}

std::vector<Row> CFileControl::ReadTable()
{
	std::vector<Row> rows;
	Row row;

	std::string str;
	while (getline(m_tableInput, str))
	{
		std::istringstream iss(str);
		getline(iss, row.symbol, '\t');
		getline(iss, str, '\t');

		std::istringstream issGuidingSymbols(str);
		while (getline(issGuidingSymbols, str, ' '))
		{
			row.guidingSymbols.push_back(str);
		}

		getline(iss, str, '\t');
		if (str == "y")
		{
			row.shift = true;
		}
		else if (str == "n")
		{
			row.shift = false;
		}

		getline(iss, str, '\t');
		if (str == "y")
		{
			row.error = true;
		}
		else if (str == "n")
		{
			row.error = false;
		}

		getline(iss, str, '\t');
		row.pointer = std::stoi(str);

		getline(iss, str, '\t');
		if (str == "y")
		{
			row.isInsertInStack = true;
		}
		else if (str == "n")
		{
			row.isInsertInStack = false;
		}

		getline(iss, str, '\t');
		if (str == "y")
		{
			row.isEnd = true;
		}
		else if (str == "n")
		{
			row.isEnd = false;
		}
		rows.push_back(row);
		row.guidingSymbols.clear();
	}
	return rows;
}

std::string CFileControl::ReadExpression()
{
	std::string expression;
	getline(m_input, expression);
	return expression;
}

void CFileControl::WriteResult(bool result)
{
	if (result)
	{
		m_output << "ok\n";
	}
	else
	{
		m_output << "error\n";
	}
}
