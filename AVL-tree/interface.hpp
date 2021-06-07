#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <map>
#include "dictionary.hpp"

class Interface
{
public:
	Interface() = delete;
	Interface(Dictionary& dict, std::istream& in, std::ostream& out);
	void start();
	void doRead(const std::string& fileName);
	void doSearch(const std::string& word);
	void doPrint(const std::string& count);
	void doAdd(const std::string& word);
	void doDelete(const std::string& word);
private:
	const std::map< std::string, void(Interface::*)(const std::string&) > commands_
	{
		{"read", &Interface::doRead},
		{"search", &Interface::doSearch},
		{"print", &Interface::doPrint},
		{"add", &Interface::doAdd},
		{"delete", &Interface::doDelete},
	};
	Dictionary& dict_;
	std::istream& in_;
	std::ostream& out_;
};

#endif
