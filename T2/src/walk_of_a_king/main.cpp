#include <stdio.h>
#include "../lib/CPUTimer/CPUTimer.h"

#define MINUS_INFINITY -1

#define NONE -2
#define END -1
#define UP_LEFT 0
#define UP_MID 1
#define UP_RIGHT 2
#define MID_LEFT 3
#define MID_RIGHT 4
#define BOT_LEFT 5
#define BOT_MID 6
#define BOT_RIGHT 7

int dx[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
int dy[8] = {-1,-1,-1, 0, 0, 1, 1, 1};

int max_prize[8][8][500];
int path[8][8][200];

int cost[8][8];
int prize[8][8];

int starting_energy;

int dim_x;
int dim_y;

int add(int x,int y)
{
	if( x == MINUS_INFINITY || y == MINUS_INFINITY )
	{
		return MINUS_INFINITY;
	}
	else
	{
		return x+y;
	}
}

void readCostAndPrizeInput()
{
	for(int j=0;j<dim_y;j++)
	{
		for(int i=0;i<dim_x;i++)
		{
			scanf(" %d",&cost[i][j]);
		}
	}
	for(int j=0;j<dim_y;j++)
	{
		for(int i=0;i<dim_x;i++)
		{
			scanf(" %d",&prize[i][j]);
		}
	}
}

void walkOfAKingBaseCase(int x,int y,int energy)
{
	if(x==0 && y==0)
	{
		max_prize[x][y][energy] = 0;
		path[x][y][energy] = END;
	}
	else
	{
		max_prize[x][y][energy] = MINUS_INFINITY;
		path[x][y][energy] = NONE;	
	}	
}

bool isOutOfBounds(int x, int y)
{
	return (x < 0 || y < 0 || x >= dim_x || y >= dim_y);
}

void walkOfAKingInductiveStep(int x,int y,int energy)
{
	int max_prize_found_yet = MINUS_INFINITY;
	int direction_of_max_prize = NONE;

	int cell_x;
	int cell_y;
	int cell_prize;
	int cell_cost;
	int cell_max_prize;
	for(int direction=UP_LEFT;direction<=BOT_RIGHT;direction++)
	{
		cell_x = x + dx[direction];
		cell_y = y + dy[direction];

		if(isOutOfBounds(cell_x,cell_y))
		{
			continue;
		}

		cell_prize = prize[cell_x][cell_y];
		cell_cost = cost[cell_x][cell_y];

		if(cell_cost > energy)
		{
			continue;
		}

		cell_max_prize = add(cell_prize,max_prize[cell_x][cell_y][energy-cell_cost]);

		if(cell_max_prize > max_prize_found_yet)
		{
			max_prize_found_yet = cell_max_prize;
			direction_of_max_prize = direction;
		}
	}

	max_prize[x][y][energy] = max_prize_found_yet;
	path[x][y][energy] = direction_of_max_prize;
}

void walkOfAKing()
{
	for(int energy=0;energy<=starting_energy;energy++)
	{
		for(int x=0;x<dim_x;x++)
		{
			for(int y=0;y<dim_y;y++)
			{
				if(energy==0)
				{
					walkOfAKingBaseCase(x,y,energy);
				}
				else
				{
					walkOfAKingInductiveStep(x,y,energy);
				}
			}
		}
	}
}

void printOutput()
{
	int best_prize = MINUS_INFINITY;
	int energy_used;
	for(int energy=0;energy<=starting_energy;energy++)
	{
		if(max_prize[0][0][energy] > best_prize)
		{
			best_prize = max_prize[0][0][energy];
			energy_used = energy;
		}
	}
	printf("Maximum Prize = %d\n",best_prize);
	printf("Stating Energy = %d\n",starting_energy);
	printf("Used Energy = %d\n",energy_used);
	printf("Energy Left = %d\n",starting_energy-energy_used);

	int x=0;
	int y=0;
	int next_x;
	int next_y;
	int current_energy=energy_used;
	printf("Path Taken:\n");
	while(path[x][y][current_energy]!=END && path[x][y][current_energy]!=NONE)
	{
		next_x= x + dx[path[x][y][current_energy]];
		next_y= y + dy[path[x][y][current_energy]];

		printf("%d %d\n",x+1,y+1);

		current_energy -= cost[next_x][next_y];

		x = next_x;
		y = next_y;
	}
	printf("%d %d\n",x+1,y+1);
	printf("\n\n");
}

int main(void)
{
	int test_case = 0;
	CPUTimer timer_total;
	int total_runs = 0;
	while(1)
	{
		scanf(" %d",&starting_energy);
		if(!starting_energy) break;
		test_case++;

		scanf(" %d %d",&dim_x,&dim_y);

		readCostAndPrizeInput();
		do
		{
			total_runs++;
			timer_total.start();
			walkOfAKing();
			timer_total.stop();
		}
		while(timer_total.getCPUTotalSecs()<5.0f);
		printf("Test Case Number %d:\n",test_case);
		printOutput();
		printf("%d runs generated in %f seconds: %f seconds/run.\n",total_runs,timer_total.getCPUTotalSecs(),timer_total.getCPUTotalSecs()/(float)total_runs);

	}
	return 0;
}