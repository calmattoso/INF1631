#ifndef ROUND_H
#define ROUND_H

#include "Match.h"
#include <vector>

using namespace std;

class Round
{
private:
	vector<Match*> matches;
public:

	Round()
	{
	}

	Round(Round &round)
	{
		matches = round.matches;
	}
	
	void deleteMatches()
	{
		for (unsigned int i = 0; i < matches.size(); i++)
			delete matches[i];
	}

	void addMatch(Match* match)
	{
		matches.push_back(match);
	}

	friend ostream& operator<<(ostream& os, const Round& round)
	{
		os << "{";
		for (unsigned int i = 0; i < round.matches.size()-1; i++)
		{
			os << *(round.matches[i]) << ",";
		}
		os << *(round.matches[round.matches.size() - 1]);
		os << "}";
		return os;
	}
	
	const Round operator+(const Round& round)
	{
		Round answer;
		answer.matches = this->matches;
		for (unsigned int i = 0; i < round.matches.size(); i++)
			answer.matches.push_back(round.matches[i]);
		return answer;
	}

};

#endif