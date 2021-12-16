#include "recursive_descent.h"
#include <fstream>
#include <iostream>

int main()
{
    std::ifstream input("input.txt");
    
    CheckExpression(input, std::cout);

    return 0;
}
