#include "testalgorithm.h"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
#include <sstream>
#include "../lib/CPUTimer/CPUTimer.h"
 
#include "Match.h"
#include "Team.h"
#include "Round.h"

#define MAX_K 20
#define MAX_K_TO_PRINT_RESULTS 3

using namespace std;

void calculateDataSize(int k,int* numTeams,int* numRounds,int* numMatches)
{
	*numTeams = pow(2, k);
	*numRounds = *numTeams - 1;
	*numMatches = (*numTeams / 2)**numRounds;
}

int main(int argc, const char * argv[])
{
	int numberOfIterations = MAX_K;

	if (argc > 1)
		numberOfIterations = atoi(argv[1]);

	CPUTimer timer;
	int totalRuns = 0;

	cout << "Initializing computation for different values of k:" << endl;
	cout << "Trying to generate rounds for k from 0 to " << numberOfIterations << endl;
	cout << "Printing rounds output for k <= " << MAX_K_TO_PRINT_RESULTS << endl;
	cout << "----------------------------------------------------" << endl;

	timer.start();
	for (int k = 0; k <= numberOfIterations; k++)
	{
		CPUTimer timerPerK;
		int runsPerK=0;
		string output;
		do
		{
			timerPerK.start();
			output = testAlgorithm(k, false);
			timerPerK.stop();
			totalRuns++;
			runsPerK++;
		} while ( timerPerK.getCPUTotalSecs() < 5.0 );

		if (k <= MAX_K_TO_PRINT_RESULTS)
		{
			timerPerK.start();
			output = testAlgorithm(k, true);
			timerPerK.stop();
			totalRuns++;
			runsPerK++;
		}

		cout << endl << "Results for k=" << k << ":" << endl << endl;

		int numTeams, numRounds, numMatches;
		calculateDataSize(k,&numTeams,&numRounds,&numMatches);

		cout << "\t" << numTeams << " teams." << endl;
		cout << "\t" << numRounds << " rounds with " << numTeams / 2 << " matches per round." << endl;
		cout << "\t" << numMatches << " total number of matches." << endl << endl;

		cout << "\t" << runsPerK << " runs in " << timerPerK.getCPUTotalSecs() << "s" << endl;
		cout << "\t" << "Average time per run: " << timerPerK.getCPUTotalSecs() / runsPerK << "s" << endl;
		cout << output;
	}

	timer.stop();

	cout << "Total time: " << timer.getCPUTotalSecs() << "s" << endl;
	cout << "Average time per run : " << timer.getCPUTotalSecs() / (double)totalRuns << "s" << endl;

}