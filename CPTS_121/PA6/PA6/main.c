/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA6
Date: March 27, 2017
Description: Making a battleship game
*/

#include "header.h"

int main(void)
{
	char player1board[10][10] = { '\0' };
	char player2board[10][10] = { '\0' };
	char player2display[10][10] = { '\0' };
	int x = 0, y = 0, first = 0, rand_or_manual = 0, xshot = 0, yshot = 0,
		checkwin1 = 0, checkwin2 = 0, hit_or_miss = 0;
	FILE *outfile = NULL;

	srand((unsigned int)time(NULL));
	
	outfile = fopen("battleship.log", "w");

	if (outfile == NULL)
	{
		printf("Error openning oufile");
	}

	if (outfile != NULL)
	{
		welcome_screen();
		system("cls");
		initialize_game_board(player1board);
		initialize_game_board(player2board);
		initialize_game_board(player2display);

		do
		{
			printf("Please select from the following menu: \n");
			printf("1. Enter positions of ships manually\n");
			printf("2. Allow the program to randomly select positions of ships\n");
			scanf("%d", &rand_or_manual);

			if (rand_or_manual == 1)
			{
				manually_place_ships_on_board(player1board);
			}
			if (rand_or_manual == 2)
			{
				randomly_place_ships_on_board(player1board);
			}
		} while ((rand_or_manual != 1) && (rand_or_manual != 2));

		randomly_place_ships_on_board(player2board);
		display_board(player1board);
		display_board(player2display);
		first = select_who_starts_first();

		//player 1 goes first
		if (first == 1)
		{
			while (checkwin1 != 1 && checkwin2 != 1)
			{
				check_if_ship_sunk(player2board, 'C');
				check_if_ship_sunk(player2board, 'B');
				check_if_ship_sunk(player2board, 'R');
				check_if_ship_sunk(player2board, 'S');
				check_if_ship_sunk(player2board, 'D');
				printf("Enter a target: \n");
				scanf("%d %d", &xshot, &yshot);
				hit_or_miss = check_shot(player2board, xshot, yshot);
				printf("Hit enter to continue: \n");
				getch();
				system("cls");
				update_board(player2board, xshot, yshot, hit_or_miss);
				update_board(player2display, xshot, yshot, hit_or_miss);
				output_current_move(xshot, yshot, hit_or_miss, outfile);
				display_board(player1board);
				display_board(player2display);

				xshot = rand_index();
				yshot = rand_index();
				printf("Computer selects: %d , %d\n", xshot, yshot);
				hit_or_miss = check_shot(player1board, xshot, yshot);
				printf("Hit enter to continue: \n");
				getch();
				system("cls");
				update_board(player1board, xshot, yshot, hit_or_miss);
				output_current_move(xshot, yshot, hit_or_miss, outfile);
				display_board(player1board);
				display_board(player2display);

				checkwin1 = is_winner(player2board);
				checkwin2 = is_winner(player1board);
			}
		}
		//player 2 goes first
		if (first == 2)
		{
			while (checkwin1 != 1 && checkwin2 != 1)
			{
				xshot = rand_index();
				yshot = rand_index();
				printf("Computer selects: %d , %d\n", xshot, yshot);
				hit_or_miss = check_shot(player1board, xshot, yshot);
				printf("Hit enter to continue: \n");
				getch();
				system("cls");
				update_board(player1board, xshot, yshot, hit_or_miss);
				output_current_move(xshot, yshot, hit_or_miss, outfile);
				display_board(player1board);
				display_board(player2display);

				check_if_ship_sunk(player2board, 'C');
				check_if_ship_sunk(player2board, 'B');
				check_if_ship_sunk(player2board, 'R');
				check_if_ship_sunk(player2board, 'S');
				check_if_ship_sunk(player2board, 'D');
				printf("Enter a target: \n");
				scanf("%d %d", &xshot, &yshot);
				hit_or_miss = check_shot(player2board, xshot, yshot);
				printf("Hit enter to continue: \n");
				getch();
				system("cls");
				update_board(player2board, xshot, yshot, hit_or_miss);
				update_board(player2display, xshot, yshot, hit_or_miss);
				output_current_move(xshot, yshot, hit_or_miss, outfile);
				display_board(player1board);
				display_board(player2display);

				checkwin1 = is_winner(player2board);
				checkwin2 = is_winner(player1board);
			}
		}

		//player 1 wins
		if (checkwin1 == 1)
		{
			printf("Player 1 wins!\n");
		}
		//player 2 wins
		if (checkwin2 == 1)
		{
			printf("Player 2 wins!\n");
		}

		fclose(outfile);
	}

	return 0;
}

