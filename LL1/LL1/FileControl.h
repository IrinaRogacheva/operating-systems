#pragma once
#include <iostream>
#include "Row.h"

class CFileControl
{
public:
	CFileControl(std::istream& tableInput, std::istream& input, std::ostream& output);
	std::vector<Row> ReadTable();
	std::string ReadExpression();
	void WriteResult(bool result);
private:
	std::istream& m_input;
	std::istream& m_tableInput;
	std::ostream& m_output;
};