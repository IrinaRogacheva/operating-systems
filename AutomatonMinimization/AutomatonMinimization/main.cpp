#include <iostream>
#include <string>
#include "windows.h"
#include "CConsoleControl.h"

/* TODO
* удаление эквивалентных состояний
* вывод минимизированного автомата
* добавить в класс Minimizer количественные характеристики автомата и упростить в связи с этим код
* создать общий класс Minimizer для классов-наследников Mealy and Moore 
* написать минимизацию автомата Мура (в частности добавить нахождение изначального класса эквивалентности)
* исправить то, что при расчете минимизации программа не возвращается в цикл (либо убрать цикл)
* исправить все поля и методы в классах (названия, добавить где нужно const)
*/

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	CConsoleControl control(cin, cout);

	cout << "Введите строку \"Ml\", если хотите минимизировать автомат Мили или строку \"Mr\", если хотите минимизировать автомат Мура" << endl << ">";
	while (!cin.eof() && !cin.fail())
	{
		try
		{
			control.HandleCommand();
		}
		catch(exception& e)
		{
			cout << e.what() << endl << ">";
		}
	}
}
