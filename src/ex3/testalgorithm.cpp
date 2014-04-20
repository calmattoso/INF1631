#include "testalgorithm.h"
#include "roundsgenerator.h"
#include "Team.h"
#include "Round.h"
#include <sstream>

using namespace std;

stringstream testAlgorithm(int k, bool generateOutput)
{
	int numberOfTeams = (int)pow(2.0, k);;
	Team** teams;

	teams = new Team*[numberOfTeams];

	for (int i = 0; i < numberOfTeams; i++)
	{
		stringstream ss;
		ss << i + 1;

		teams[i] = new Team(ss.str().c_str());
	}

	Round* rounds = generateRounds(k, teams);

	stringstream output;
	if (generateOutput)
	{
		output << "\tRounds generated:" << endl;
		for (int i = 0; i < numberOfTeams - 1; i++)
			output << "\t\tRound " << i + 1 << ": " << rounds[i] << endl;
	}

	for (int i = 0; i < numberOfTeams - 1; i++)
		rounds[i].deleteMatches();
	delete[] rounds;
	for (int i = 0; i < numberOfTeams; i++)
		delete teams[i];
	delete[] teams;
	return output;
}
