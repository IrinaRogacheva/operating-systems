#pragma once
#include <istream>
#include <string>
#include <vector>
#include "Row.h"

class CTableRunner
{
public:
	CTableRunner(std::vector<Row>);
	bool Run(const std::string& expression);
private:
	std::vector<Row> m_table;
};