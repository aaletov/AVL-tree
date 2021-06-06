#include <iostream>
#include <vector>
#include <Windows.h>
#include "interface.hpp"

int main()
{
	std::locale::global(std::locale("Russian"));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	try
	{
		Dictionary dict;
		Interface inter(dict, std::cin, std::cout);
		inter.start();
	}
	catch (const std::exception& exc)
	{
		std::cerr << exc.what() << '\n';
		return 1;
	}
	return 0;
}