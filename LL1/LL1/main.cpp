#include <iostream>
#include <fstream>
#include "FileControl.h"
#include "TableRunner.h"

int main()
{
    std::ifstream input("input.txt");
    std::ifstream tableFile("table.txt");
    std::ofstream output("output.txt");

    CFileControl fileControl(tableFile, input, output);
    std::vector<Row> table = fileControl.ReadTable();

    CTableRunner tableRunner(table);
    std::string expression = fileControl.ReadExpression();
    fileControl.WriteResult(tableRunner.Run(expression));
}

