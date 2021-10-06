#include <iostream>
#include <string>
#include "windows.h"
#include "CConsoleControl.h"
#include <fstream>

/* TODO
* удаление эквивалентных состояний
* вывод минимизированного автомата
* добавить в класс Minimizer количественные характеристики автомата и упростить в связи с этим код
* создать общий класс Minimizer для классов-наследников Mealy and Moore 
* написать минимизацию автомата Мура (в частности добавить нахождение изначального класса эквивалентности)
* исправить то, что при расчете минимизации программа не возвращается в цикл (либо убрать цикл)
* исправить все поля и методы в классах (названия, добавить где нужно const)
* исправить ввод с консоли на ввод из файла
*/

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	CConsoleControl control(input, output);
	control.HandleCommand();
}
