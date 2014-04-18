#ifndef TEAM_H
#define TEAM_H

#include <cstring>
#include <iostream>

using namespace std;

class Team
{
private:
	char* name;
public:
	Team(const char* _name)
	{
		name = new char[strlen(_name)+1];
		strcpy(name, _name);
	}

	~Team()
	{
		delete[] name;
	}

	Team(Team &team)
	{
		name = team.name;
	}

	friend ostream& operator<<(ostream& os, const Team& team)
	{
		os << team.name;
		return os;
	}
};

#endif