#include "interface.hpp"
#include <fstream>
#include <locale>

Interface::Interface(Dictionary& dict, std::istream& in, std::ostream& out):
	dict_(dict),
	in_(in),
	out_(out)
{}

void Interface::start()
{
	out_ << "Commands:" << '\n'
		<< "read [filename] - read file and add it to dictionary" << '\n'
		<< "search [word] - search word in dictionary and print number of occurrences" << '\n'
		<< "print [count] - print count of most frequent words" << '\n'
		<< "add [word] - add word to dictionary" << '\n'
		<< "delete [word] - delete word from dictionary" << '\n'
		<< "quit - closes interface" << '\n';
	std::string command;
	std::string param;
	while (true)
	{
		//in_.clear();
		in_ >> command;
		if (in_.fail() || in_.eof() || !command.compare("quit"))
		{
			break;
		}
		in_ >> param;
		if (in_.fail() || in_.eof())
		{
			break;
		}
		if (dict_.getMaxByValue() == Dictionary::npos && command != "read" && command != "add")
		{
			out_ << "Dictionary is empty" << '\n';
			continue;
		}
		try
		{
			(this->*commands_.at(command))(param);
		}
		catch (const std::out_of_range& exc)
		{
			out_ << "Incorrect command" << '\n';
		}
	}
	out_ << "Interface was closed" << '\n';
}

void Interface::doRead(const std::string& fileName)
{
	long long unsigned counter = 0;
	std::ifstream fs;
	do
	{
		fs.open(fileName);
		if (!(fs.is_open()))
		{
			out_ << "File opening error" << '\n';
			return;
		}
		else
		{
			break;
		}
	} while (true);
	std::string word;
	while (!(fs.eof() || fs.fail()))
	{

		fs >> word;
		formatWord(word);
		if (!filterWord(word))
		{
			continue;
		}
		counter++;
		if (counter % 10000 == 0)
		{
			out_ << "Read " << counter / 10000 << "0000\n";
		}
		if (dict_.search(word))
		{
			dict_.incrKey(word);
		}
		else
		{
			dict_.insert({ word, 1 });
		}
	}
	fs.close();
	out_ << "File was successfully read\n";
}

void Interface::doSearch(const std::string& word)
{
	std::locale loc("Russian");
	auto myLower = [loc](char& c) mutable
	{
		c = std::tolower(c, loc);
	};
	std::string lower(word);
	std::for_each(lower.begin(), lower.end(), myLower);
	if (!dict_.search(word))
	{
		out_ << "No such word in dictionary" << '\n';
		return;
	}
	out_ << word << ' ' << dict_.at(word) << '\n';
}

void Interface::doPrint(const std::string& count)
{
	using namespace std::placeholders;
	int intCount;
	if (std::all_of(count.begin(), count.end(), isdigit))
	{
		intCount = std::stoi(count);
	}
	else
	{
		out_ << "Incorrect param" << '\n';
		return;
	}
	Dictionary copyDict(dict_);
	Dictionary::value_type max;
	for (int i = 1; i < intCount + 1; i++)
	{
		max = copyDict.getMaxByValue();
		if (max == Dictionary::npos)
		{
			std::cout << "No more words" << '\n';
			break;
		}
		std::cout << i << " place is word \"" << std::get< 0 >(max) << "\" " << std::get< 1 >(max) << " occurrences\n";
		copyDict.deleteKey(std::get< 0 >(max));
	}
}

void Interface::doAdd(const std::string& word)
{
	if (!filterWord(word))
	{
		out_ << "Incorrect word format" << '\n';
		return;
	}
	if (dict_.search(word))
	{
		dict_.incrKey(word);
	}
	else
	{
		dict_.insert({ word, 1 });
	}
}

void Interface::doDelete(const std::string& word)
{
	if (!filterWord(word))
	{
		out_ << "Incorrect word format" << '\n';
		return;
	}
	if (!dict_.search(word))
	{
		out_ << "No such word in dictionary" << '\n';
		return;
	}
	dict_.deleteKey(word);
}