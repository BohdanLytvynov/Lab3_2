// Lab3_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include"ukrString.h"
#include<Conio.h>
#include<string>
#include<crtdbg.h>
#include<algorithm>
#include<vector>

using Word = strings::ukrString;

namespace lab
{
	template<class Tout, class Tmsg>
	static Tout Input(const Tmsg& msg, std::function<Tout(std::string& str)> converter,
		std::function<bool(std::string& str, Tmsg& error)> validator = nullptr)
	{
		Tmsg error;

		std::string str;

		do
		{
			std::cout << msg << std::endl;

			std::getline(std::cin, str);

			if (!validator)
				break;

			if (validator(str, error))
				break;
			else
				std::cout << error << std::endl;

		} while (true);

		return converter(str);
	}	
}

auto com_converter = [](std::string& str)->char
{
	return *str.c_str();
};

auto com_validator = [](std::string& str, strings::ukrString& error)->bool
{
	int res = 0;

	try
	{
		res = std::stoi(str);
	}
	catch (...)
	{
		error = "Невірний ввод!";
		return false;
	}

	if (res < 1 && res > 3)
	{
		error = "Невірний діапазон при введені команди!";
	}

	return true;
};

auto size_validator = [](std::string& str, strings::ukrString& error) ->bool
{
	int res = 0;
	try
	{
		res = std::stoi(str);
	}
	catch (...)
	{
		error = "Невірний ввод!";
		return false;
	}

	if (res <= 0)
	{
		error = "Кількість рядків не може бути 0 або від'ємним числом!";
		return false;
	}

	return true;
};

static bool sort_Pred(const strings::ukrString& str1, const strings::ukrString& str2)
{
	return str1.getLength() > str2.getLength();
}

int main()
{	
    using namespace strings;
	using namespace std;
	using namespace lab;

	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(flag);

    cout << ukrString("Лабораторна робота 3");
	char key;

	do
	{
		key = Input<char, ukrString>(ukrString("\n\nВиберіть опцію:\n \t-1 -> Виконати завдання за варіантом. \n\t-2 -> Вийти з програмии."), 
			com_converter, com_validator);
				
		if (key == '1')
		{
			cout << ukrString("Вибрана опція: \"Виконати завдвння за варіантом.\" \n\t Пошук найбільшого з рядків зі списка рядків, що ввів користувач.") << endl;

			int rowCount = Input<int, ukrString>(ukrString("\nВведіть кількість рядків:(Число має бути цілим та додатнім)"),
				[](std::string& str)->int {return std::stoi(str); }, size_validator);

			Word* text = new Word[rowCount];

			strings::ukrString str("Введіть рядок: ");
			
			for (size_t i = 0; i < rowCount; i++)
			{				
				cout << str << endl;
				//str.use_for_input();
				ukrString::getLine(cin, text[i]);
				text[i].use_for_input();
			}

			std::sort(text, text + rowCount, sort_Pred);

			cout << ukrString("\n\tРезультат:\n") << endl;

			for (size_t i = 0; i < rowCount; i++)
			{
				cout << text[i]<< endl;
			}
		}

	} while (key != '2');

    return 0;
}


