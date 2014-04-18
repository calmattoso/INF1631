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

	// A total of numberOfTeams-1 should be generated
	rounds = new Round[numberOfTeams-1];

	// Base Cases
	if (k == 0)
	{
		// k=0 results in 1 team.
		// There are not enough teams to generate a match. So, no rounds are supposed to be generated.
	}
	if (k == 1)
	{
		// k=1 results in 2 teams.
		// In this case, only one round containing the match between the teams is supposed to be generated.
		rounds[0].addMatch(new Match(teams[0], teams[1]));
	}
	// Recursion Step
	else
	{
		int halfTheNumberOfTeams = numberOfTeams / 2; // halfTheNumberOfTeams is an integer because numberOfTeams is always even

		Team** teamsFirstHalf = teams;
		Team** teamsSecondHalf = teams + halfTheNumberOfTeams;

		// Induction Hypothesis: It's known how to generate the rounds for the first half of the teams (k-1) and for the second half (k-1) as well.
		// firstHalfTeamsRounds and secondHalfTeamsTeamsRounds should point to an array containing (n/2)-1 rounds.
		Round* firstHalfTeamsRounds = generateRounds(k - 1, teamsFirstHalf);
		Round* secondHalfTeamsTeamsRounds = generateRounds(k - 1, teamsSecondHalf);

		// Generates the first (n/2)-1 rounds based on the rounds generated for the first and second half of the teams.
		// Round[i] = Round1stHalf[i] U Round2ndHalf[i], i=1..(n/2)-1
		// After this step, the only matches missing should be the matches between the first and second half sets of teams.
		for (int i = 1; i <= halfTheNumberOfTeams-1; i++)
			rounds[i-1] = firstHalfTeamsRounds[i-1] + secondHalfTeamsTeamsRounds[i-1]; // The operator+ indicates a SET UNION operator.

		delete[] firstHalfTeamsRounds;
		delete[] secondHalfTeamsTeamsRounds;

		// Generates the rounds between the first and second half sets of teams.
		// Round[(n/2)+t] = {(e[1+((j+t)%(n/2))],e[j+(n/2)]), j=1..(n/2)}, t =0..(n/2)-1.
		for (int t = 0; t <= halfTheNumberOfTeams - 1; t++) // Rounds iterator
			for (int j = 1; j <= halfTheNumberOfTeams; j++) // Teams matching iterator
				rounds[halfTheNumberOfTeams + t-1].addMatch(new Match(teams[1 + ((j + t) % halfTheNumberOfTeams) -1], teams[j + halfTheNumberOfTeams -1]));
	}

	return rounds;
}
