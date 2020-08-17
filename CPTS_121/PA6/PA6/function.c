/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA6
Date: March 27, 2017
Description: Making a battleship game
*/

#include "header.h"

void welcome_screen(void)
{
	printf("***** Welcome To Battleship *****\n");
	printf("1. This is a two player game\n");
	printf("2. Player1 is you and Player2 is the computer\n");
	printf("3. There is a 10 by 10 grid on which to place 5 ships\n");
	printf("4. Carrier (5 cells), Battleship (4 cells), Cruiser (3 cells),\n");
	printf("   Submarine (3 cells), Destroyer (2 cells)\n");
	printf("5. You may place your ships manually or randomly horizonal or vertically\n");
	printf("6. Person who starts first will be chosen randomly\n");
	printf("7. Players will take turns choosing a coordinate to fire upon\n");
	printf("8. Winner is first to sink all 5 enemy ships\n\n");
	printf("Hit enter to start game!");
	getch();
}

void initialize_game_board(char playerboard[10][10])
{
	int i = 0, j = 0;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			playerboard[i][j] = '~';
			/*printf("%c", playerboard[i][j]);*/
		}
	}
}

int select_who_starts_first()
{
	int player = 0;

	player = (rand() % 2) + 1;

	return player;
}

int rand_index()
{
	int index = 0;

	index = (rand() % 10);

	return index;
}

void manually_place_ships_on_board(char playerboard[10][10])
{
	int x1 = 0, x2 = 0, x3 = 0, x4 = 0, x5 = 0;
	int y1 = 0, y2 = 0, y3 = 0, y4 = 0, y5 = 0;

	//Carrier
	do
	{
		printf("Please enter the 5 cells to place the carrier across (row,column)\n");
		scanf("%d %d %d %d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4, &x5, &y5);
		playerboard[x1][y1] = 'C';
		playerboard[x2][y2] = 'C';
		playerboard[x3][y3] = 'C';
		playerboard[x4][y4] = 'C';
		playerboard[x5][y5] = 'C';
	} while (((x1 == x2) && (x2 == x3) && (x3 == x4) && (x4 == x5)) ||
		((y1 == y2) && (y2 == y3) && (y3 == y4) && (y4 == y5)) && 
		(((x2 == x1 + 1) && (x3 == x2 + 1) && (x4 == x3 + 1) && (x5 == x4 + 1))||
		((y2 == y1 + 1) && (y3 == y2 + 1) && (y4 == y3 + 1) && (y5 == y4 + 1))));

	//Battleship
	do
	{
		printf("Please enter the 4 cells to place the battleship across (row,column)\n");
		scanf("%d %d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		if ((playerboard[x1][y1] == '~') && (playerboard[x2][y2] == '~')
			&& (playerboard[x3][y3] == '~') && (playerboard[x4][y4] == '~')
			&& (((x1 == x2) && (x2 == x3) && (x3 == x4)) || 
			((y1 == y2) && (y2 == y3) && (y3 == y4))))
		{
			playerboard[x1][y1] = 'B';
			playerboard[x2][y2] = 'B';
			playerboard[x3][y3] = 'B';
			playerboard[x4][y4] = 'B';
		}
		else
		{
			printf("Input not valid choose new coordinates\n");
		}
	} while (playerboard[x1][y1] != 'B');

	//Cruiser
	do
	{
		printf("Please enter the 3 cells to place the cruiser across (row,column)\n");
		scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
		if ((playerboard[x1][y1] == '~') && (playerboard[x2][y2] == '~')
			&& (playerboard[x3][y3] == '~')
			&& (((x1 == x2) && (x2 == x3)) || ((y1 == y2) && (y2 == y3))))
		{
			playerboard[x1][y1] = 'R';
			playerboard[x2][y2] = 'R';
			playerboard[x3][y3] = 'R';
		}
		else
		{
			printf("Input not valid choose new coordinates\n");
		}
	} while (playerboard[x1][y1] != 'R');

	//Submarine
	do
	{
		printf("Please enter the 3 cells to place the submarine across (row,column)\n");
		scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
		if ((playerboard[x1][y1] == '~') && (playerboard[x2][y2] == '~')
			&& (playerboard[x3][y3] == '~')
			&& (((x1 == x2) && (x2 == x3)) || ((y1 == y2) && (y2 == y3))))
		{
			playerboard[x1][y1] = 'S';
			playerboard[x2][y2] = 'S';
			playerboard[x3][y3] = 'S';
		}
		else
		{
			printf("Input not valid choose new coordinates\n");
		}
	} while (playerboard[x1][y1] != 'S');

	//Destroyer
	do
	{
		printf("Please enter the 2 cells to place the destroyer across (row,column)\n");
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		if ((playerboard[x1][y1] == '~') && (playerboard[x2][y2] == '~') && ((x1 == x2) || (y1 == y2)))
		{
			playerboard[x1][y1] = 'D';
			playerboard[x2][y2] = 'D';
		}
		else
		{
			printf("Input not valid choose new coordinates\n");
		}
	} while (playerboard[x1][y1] != 'D');
}

void randomly_place_ships_on_board(char playerboard[10][10])
{
	int x = 0, y = 0;
	int select = 0, i = 0;

	select = select_who_starts_first();
	//Carrier
	if (select == 1)
	{
		x = rand_index();
		y = (rand_index() + 1) % 5;
		for (i = 0; i < 5; i++)
		{
			playerboard[x][y + i] = 'C';
		}
	}
	if (select == 2)
	{
		x = (rand_index() + 1) % 5;
		y = rand_index();
		for (i = 0; i < 5; i++)
		{
			playerboard[x + i][y] = 'C';
		}
	}

	select = select_who_starts_first();
	//Battleship
	if (select == 1)
	{
		do
		{
			x = rand_index();
			y = (rand_index() + 1) % 4;

		} while ((playerboard[x][y] != '~') || (playerboard[x][y + 1] != '~')
			|| (playerboard[x][y + 2] != '~') || (playerboard[x][y + 3] != '~'));

		for (i = 0; i < 4; i++)
		{
			playerboard[x][y + i] = 'B';
		}
	}
	if (select == 2)
	{
		do
		{
			x = (rand_index() + 1) % 5;
			y = rand_index();

		} while ((playerboard[x][y] != '~') || (playerboard[x + 1][y] != '~')
			|| (playerboard[x + 2][y] != '~') || (playerboard[x + 3][y] != '~'));

		for (i = 0; i < 4; i++)
		{
			playerboard[x + i][y] = 'B';
		}
	}

	select = select_who_starts_first();
	//Cruiser
	if (select == 1)
	{
		do
		{
			x = rand_index();
			y = (rand_index() + 1) % 4;

		} while ((playerboard[x][y] != '~') || (playerboard[x][y + 1] != '~')
			|| (playerboard[x][y + 2] != '~'));

		for (i = 0; i < 3; i++)
		{
			playerboard[x][y + i] = 'R';
		}
	}
	if (select == 2)
	{
		do
		{
			x = (rand_index() + 1) % 4;
			y = rand_index();

		} while ((playerboard[x][y] != '~') || (playerboard[x + 1][y] != '~')
			|| (playerboard[x + 1][y] != '~'));

		for (i = 0; i < 3; i++)
		{
			playerboard[x + i][y] = 'R';
		}
	}

	select = select_who_starts_first();
	//Submarine
	if (select == 1)
	{
		do
		{
			x = rand_index();
			y = (rand_index() + 1) % 4;

		} while ((playerboard[x][y] != '~') || (playerboard[x][y + 1] != '~')
			|| (playerboard[x][y + 2] != '~'));

		for (i = 0; i < 3; i++)
		{
			playerboard[x][y + i] = 'S';
		}
	}
	if (select == 2)
	{
		do
		{
			x = (rand_index() + 1) % 4;
			y = rand_index();

		} while ((playerboard[x][y] != '~') || (playerboard[x + 1][y] != '~')
			|| (playerboard[x + 1][y] != '~'));

		for (i = 0; i < 3; i++)
		{
			playerboard[x + i][y] = 'S';
		}
	}

	select = select_who_starts_first();
	//Destroyer
	if (select == 1)
	{
		do
		{
			x = rand_index();
			y = (rand_index() + 1) % 3;

		} while ((playerboard[x][y] != '~') || (playerboard[x][y + 1] != '~'));

		for (i = 0; i < 2; i++)
		{
			playerboard[x][y + i] = 'D';
		}
	}
	if (select == 2)
	{
		do
		{
			x = (rand_index() + 1) % 3;
			y = rand_index();

		} while ((playerboard[x][y] != '~') || (playerboard[x + 1][y] != '~'));

		for (i = 0; i < 2; i++)
		{
			playerboard[x + i][y] = 'D';
		}
	}
}

int check_shot(char playerboard[10][10], int x, int y)
{
	if (playerboard[x][y] == 'C' || playerboard[x][y] == 'B' ||
		playerboard[x][y] == 'R' || playerboard[x][y] == 'S' ||
		playerboard[x][y] == 'D' || playerboard[x][y] == '*')
	{
		printf("%d , %d is a hit\n", x, y);
		return 1;
	}
	else
	{
		printf("%d , %d is a miss\n", x, y);
		return 0;
	}
}

int is_winner(char playerboard[10][10])
{
	int i = 0, j = 0;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (playerboard[i][j] == 'C' || playerboard[i][j] == 'B' ||
				playerboard[i][j] == 'R' || playerboard[i][j] == 'S' ||
				playerboard[i][j] == 'D')
			{
				return 0;
			}
		}
	}
	return 1;
}

void update_board(char playerboard[10][10], int x, int y, int hit)
{
	if (hit == 0)
	{
		playerboard[x][y] = 'm';
	}
	if (hit == 1)
	{
		playerboard[x][y] = '*';
	}
}

void display_board(char playerboard[10][10])
{
	int i = 0, j = 0;

	printf("   0  1  2  3  4  5  6  7  8  9");
	for (i = 0; i < 10; i++)
	{
		printf("\n%d  ", i);
		for (j = 0; j < 10; j++)
		{
			printf("%c  ", playerboard[i][j]);
		}
	}
	printf("\n\n");
}

int output_current_move(int x, int y, int hit, FILE *outfile)
{
	if (hit == 1)
	{
		fprintf(outfile, "%d , %d is a hit!\n", x, y);
	}
	if (hit == 0)
	{
		fprintf(outfile, "%d , %d is a miss!\n", x, y);
	}
}

void check_if_ship_sunk(char playerboard[10][10], char ship)
{
	int i = 0, j = 0;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (playerboard[i][j] == ship)
			{
				return;
			}
		}
	}
	if (ship == 'C')
	{
		printf("Carrier is sunk!\n");
	}
	else if (ship == 'B')
	{
		printf("Battleship is sunk!\n");
	}
	else if (ship == 'R')
	{
		printf("Cruiser is sunk!\n");
	}
	else if (ship == 'S')
	{
		printf("Submarine is sunk!\n");
	}
	else if (ship == 'D')
	{
		printf("Destroyer is sunk!\n");
	}
}

void output_stats()
{

}