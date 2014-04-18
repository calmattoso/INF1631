#ifndef MATCH_H
#define MATCH_H

#include "Team.h"

class Match
{
private:
	Team* team1;
	Team* team2;
public:
	Match(Team* _team1, Team* _team2)
	{
		team1 = _team1;
		team2 = _team2;
	}

	Match(Match &match)
	{
		team1 = match.team1;
		team2 = match.team2;
	}

	friend ostream& operator<<(ostream& os, const Match& match)
	{
		os << "(" << *(match.team1) << "," << *(match.team2) << ")";
		return os;
	}
};


#endif