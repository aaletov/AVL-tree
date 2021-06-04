#include <iostream>
#include <vector>
#include "interface.hpp"

int main()
{
	setlocale(LC_ALL, "Russian");
	try
	{
		Dictionary dict;
		Interface inter(dict, std::cin, std::cout);
		inter.start();
	}
	catch (const std::exception& exc)
	{
		std::cerr << exc.what();
		return -2;
	}
	return 0;
}