#pragma once

#include <string>
using std::string;
class Room
{
private: int layouts[2];
public:
	Room();
	~Room();
	void addLayouts(string path);
	int randomLayout();
};

