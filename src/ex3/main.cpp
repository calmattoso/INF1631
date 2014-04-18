#include "Match.h"
#include "Round.h"
#include "Team.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>

using namespace std;

Round* generateRounds(int k, Team** teams);

int main(void)
{
	int k;
	int numberOfTeams;

	Team** teams;

	printf("Type the k amount of the 2^k teams: ");
	scanf(" %d",&k);

	numberOfTeams = (int) pow(2.0,k);

	teams = new Team*[numberOfTeams];

	for (int i = 0; i < numberOfTeams; i++)
	{
		char teamName[30];
		//cout << "Team " << i << "'s name:" << endl;
		printf("Team %d's name: ", i);
		scanf(" %[^\n]", teamName);
		
		teams[i] = new Team(teamName);
	}

	Round* rounds = generateRounds(k,teams);

	cout << "Rounds generated:" << endl;
	for (int i = 0; i < numberOfTeams - 1; i++)
		cout << "Round " << i+1 << ": " << rounds[i] << endl;

	for (int i = 0; i < numberOfTeams - 1; i++)
		rounds[i].deleteMatches();
	delete[] rounds;
	for (int i = 0; i < numberOfTeams; i++) 
		delete teams[i];
	delete[] teams;

}

Round* generateRounds(int k, Team** teams)
{
	Round* rounds;
	int numberOfTeams = (int) pow(2.0, k);

	rounds = new Round[numberOfTeams];

	//if (k == 0){}
	if (k == 1)
	{
		rounds[0].addMatch(new Match(teams[0], teams[1]));
	}
	else
	{
		int halfTheNumberOfTeams = numberOfTeams / 2;
		Team** teamsFirstHalf = teams;
		Team** teamsSecondHalf = teams + halfTheNumberOfTeams;

		Round* firstHalfTeamsRounds = generateRounds(k - 1, teamsFirstHalf);
		Round* secondHalfTeamsTeamsRounds = generateRounds(k - 1, teamsSecondHalf);

		for (int i = 0; i < halfTheNumberOfTeams; i++)
			rounds[i] = firstHalfTeamsRounds[i] + secondHalfTeamsTeamsRounds[i];

		delete[] firstHalfTeamsRounds;
		delete[] secondHalfTeamsTeamsRounds;

		for (int t = 0; t <= halfTheNumberOfTeams - 1; t++)
		for (int j = 1; j <= halfTheNumberOfTeams; j++)
			rounds[halfTheNumberOfTeams + t-1].addMatch(new Match(teams[1 + ((j + t) % halfTheNumberOfTeams) -1], teams[j + halfTheNumberOfTeams -1]));
	}

	return rounds;
}
