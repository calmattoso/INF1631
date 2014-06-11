#include <stdio.h>
#include <unistd.h>
#include <GL/glut.h>
#include <string.h>

#define STEP 1

#define MINUS_INFINITY -1

#define WIDTH 600
#define HEIGHT 600

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

int king_x=0;
int king_y=0;
int king_prize=0;
int king_energy=0;

bool casa_percorrida[8][8];

void printWord(float px,float py,char* w)
{
	int size = strlen(w);
	for(int i=0;i<size;i++)
	{
		glRasterPos2f(px+i*0.025 , py);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13,w[i]);
	}
}

void drawBoard()
{
	char word_custo[7] = "Custo:";
	char word_premio[8] = "Premio:";
	char word_energia[9] = "Energia:";
	char custo_valor[30];
	char premio_valor[30];
	float step_x = 2.0/dim_x;
	float step_y = 2.0/dim_y;

	float x;
	float y;
	for(int ix=0;ix<dim_x;ix++)
	{	
		for(int iy=0;iy<dim_y;iy++)
		{
			x = step_x * ix - 1;
			y = 1-(step_y * iy);

			if(casa_percorrida[ix][iy])
			{		
				glColor3f(0.3,0.3,0.5);
				glBegin(GL_QUADS);
					glVertex2d(x,y);
					glVertex2d(x+step_x,y);
					glVertex2d(x+step_x,y-step_y);
					glVertex2d(x,y-step_y);
				glEnd();
			}

			glColor3f(1.0,1.0,1.0);
			glBegin(GL_LINE_STRIP);
				glVertex2d(x,y);
				glVertex2d(x+step_x,y);
				glVertex2d(x+step_x,y-step_y);
				glVertex2d(x,y-step_y);
			glEnd();
			
			glColor3f(1.0f, 1.0f, 1.0f);
			printWord(x+0.01,y-0.05,word_custo);
			sprintf(custo_valor, "%d", cost[ix][iy]);
			glColor3f(1.0f, 0.0f, 0.0f);
			printWord(x+0.01,y-0.10,custo_valor);
			glColor3f(1.0f, 1.0f, 1.0f);
			printWord(x+0.01,y-0.15,word_premio);
			sprintf(premio_valor, "%d", prize[ix][iy]);
			glColor3f(0.0f, 1.0f, 0.0f);
			printWord(x+0.01,y-0.20,premio_valor);
		}
	}

	x = step_x * king_x - 1;
	y = 1-(step_y * king_y);

	float x_mid = x+step_x/2.0;
	float y_mid = y-step_y/2.0;

	glColor3f(0.0,0.0,1.0);
	glBegin(GL_TRIANGLES);
		glVertex2d(x_mid+0.2,y_mid+0.2);
		glVertex2d(x_mid+0.2,y_mid-0.2);
		glVertex2d(x_mid,y_mid);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2d(x_mid+0.2,y_mid-0.15);
		glVertex2d(x_mid+0.2,y_mid+0.15);
		glVertex2d(x_mid+0.4,y_mid+0.15);
		glVertex2d(x_mid+0.4,y_mid-0.15);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	printWord(x_mid+0.12,y_mid+0.06,word_energia);

	sprintf(custo_valor, "%d", king_energy);
	glColor3f(0.0f, 1.0f, 0.0f);
	printWord(x_mid+0.12,y_mid+0.01,custo_valor);

	glColor3f(1.0f, 1.0f, 1.0f);
	printWord(x_mid+0.12,y_mid-0.04,word_premio);

	sprintf(premio_valor, "%d", king_prize);
	glColor3f(0.0f, 1.0f, 0.0f);
	printWord(x_mid+0.12,y_mid-0.09,premio_valor);
}

void draw(void)
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	drawBoard();
	glFlush();
}


void printDirection(int direction)
{
	switch(direction)
	{
		case NONE:
			printf("[NONE] ");
			break;
		case END:
			printf("[END] ");
			break;
		case UP_LEFT:
			printf("[^<] ");
			break;
		case UP_MID:
			printf("[^] ");
			break;
		case UP_RIGHT:
			printf("[>^] ");
			break;
		case MID_LEFT:
			printf("[<] ");
			break;
		case MID_RIGHT:
			printf("[>] ");
			break;
		case BOT_LEFT:
			printf("[V<] ");
			break;
		case BOT_MID:
			printf("[V] ");
			break;
		case BOT_RIGHT:
			printf("[>V] ");
			break;
		default:
			printf("An error has occurred. ");
			break;
	}
}

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
	printf("Energy Left = %d\n",starting_energy-energy_used);

	for(int x=0;x<dim_x;x++)
	{
		for(int y=0;y<dim_y;y++)
		{
			casa_percorrida[x][y] = false;
		}
	}

	int x=0;
	int y=0;
	int next_x;
	int next_y;
	int current_energy=energy_used;
	king_energy = starting_energy;
	king_prize = 0;
	printf("Path Taken:\n");
	while(path[x][y][current_energy]!=END && path[x][y][current_energy]!=NONE)
	{
		next_x= x + dx[path[x][y][current_energy]];
		next_y= y + dy[path[x][y][current_energy]];

		printf("%d %d\n",x+1,y+1);

		king_x=x;
		king_y=y;
		casa_percorrida[x][y]=true;
		draw();
		sleep(STEP);
		king_energy-=cost[next_x][next_y];
		king_prize+=prize[next_x][next_y];

		current_energy -= cost[next_x][next_y];

		x = next_x;
		y = next_y;
	}
	printf("%d %d\n",x+1,y+1);
	king_x=x;
	king_y=y;
	draw();
	sleep(2*STEP);
}

int runAlgorithm()
{
	int test_case = 0;
	while(1)
	{
		scanf(" %d",&starting_energy);
		if(!starting_energy) break;
		test_case++;

		scanf(" %d %d",&dim_x,&dim_y);

		readCostAndPrizeInput();

		walkOfAKing();
		printf("Test Case Number %d:\n",test_case);
		printOutput();
	}
	return 0;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH,HEIGHT);
	glOrtho(0,WIDTH,HEIGHT,0,0,10);
	glutCreateWindow("Walk Of A King");
	runAlgorithm();
	return 0;
}