/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA5
Date: Febuary 24, 2017
Description: Making a yahtzee
*/

#include "header.h"

int roll_die(void)
{
	int die = 0;

	die = (rand() % 6) + 1;

	return die;
}

void roll_dice1(int dice[], int max_items)
{
	int index = 0;

	while (index < max_items)
	{
		dice[index] = roll_die();
		++index;
	}
	printf("(1)  (2)  (3)  (4)  (5)\n");
	printf(" %d    %d    %d    %d    %d\n\n",
		dice[0], dice[1], dice[2], dice[3], dice[4]);
}

void reroll_dice(int dice[], int size)
{
	int rolls = 0, die = 0, index = 0;

	printf("How many dice do you want to reroll?");
	scanf("%d", &rolls);

	for (die = 0; die < rolls; die++)
	{
		printf("Which die do you want to reroll?\n");
		scanf("%d", &index);
		dice[index - 1] = roll_die();
	}
	system("cls");
	printf("(1)  (2)  (3)  (4)  (5)\n");
	printf(" %d    %d    %d    %d    %d\n\n",
		dice[0], dice[1], dice[2], dice[3], dice[4]);
}

void print_score_card(int scorecard[])
{
	printf("1)  Ones            -> sum of all ones    ->  %d\n", scorecard[0]);
	printf("2)  Twos            -> sum of all twos    ->  %d\n", scorecard[1]);
	printf("3)  Threes          -> sum of all threes  ->  %d\n", scorecard[2]);
	printf("4)  Fours           -> sum of all fours   ->  %d\n", scorecard[3]);
	printf("5)  Fives           -> sum of all fives   ->  %d\n", scorecard[4]);
	printf("6)  Sixes           -> sum of all sixes   ->  %d\n", scorecard[5]);
	printf("7)  Three-of-a-kind -> sum of all dice    ->  %d\n", scorecard[6]);
	printf("8)  Four-of-a-kind  -> sum of all dice    ->  %d\n", scorecard[7]);
	printf("9)  Full house      ->        25          ->  %d\n", scorecard[8]);
	printf("10) Small straight  ->        30          ->  %d\n", scorecard[9]);
	printf("11) Large straight  ->        40          ->  %d\n", scorecard[10]);
	printf("12) Yahtzee         ->        50          ->  %d\n", scorecard[11]);
	printf("13) Chance          -> sum of all dice    ->  %d\n\n", scorecard[12]);
}

void count_die_values(int dice[], int size, int *one_ptr, int *two_ptr,
	int *three_ptr, int *four_ptr, int *five_ptr, int *six_ptr)
{
	int index = 0;

	//*one_ptr = 0;
	//*two_ptr = 0;
	//*three_ptr = 0;
	//*four_ptr = 0;
	//*five_ptr = 0;
	//*six_ptr = 0;

	for (index = 0; index < size; ++index)
	{
		if (dice[index] == 1)
		{
			*one_ptr += 1;
		}
		if (dice[index] == 2)
		{
			*two_ptr += 1;
		}
		if (dice[index] == 3)
		{
			*three_ptr += 1;
		}
		if (dice[index] == 4)
		{
			*four_ptr += 1;
		}
		if (dice[index] == 5)
		{
			*five_ptr += 1;
		}
		if (dice[index] == 6)
		{
			*six_ptr += 1;
		}
	}
}

void check_score(int dice[], int scoring[], int used[], int size, int score,
	int num1, int num2, int num3, int num4, int num5, int num6)
{
	int i = 0;

	if (used[score - 1] == 1)
	{
		do
		{
			printf("This combination has already been used, select another: ");
			scanf("%d", &score);
		} while (used[score - 1] == 1);
	}

	if (used[score - 1] == 0)
	{
		if (score == 1)
		{
			scoring[0] = num1;
			used[score - 1] = 1;
		}
		if (score == 2)
		{
			scoring[1] = num2 * 2;
			used[score - 1] = 1;
		}
		if (score == 3)
		{
			scoring[2] = num3 * 3;
			used[score - 1] = 1;
		}
		if (score == 4)
		{
			scoring[3] = num4 * 4;
			used[score - 1] = 1;
		}
		if (score == 5)
		{
			scoring[4] = num5 * 5;
			used[score - 1] = 1;
		}
		if (score == 6)
		{
			scoring[5] = num6 * 6;
			used[score - 1] = 1;
		}
		if (score == 7)
		{
			if (num1 == 3 || num2 == 3 || num3 == 3 || num4 == 3 || num5 == 3 || num6 == 3)
			{
				for (i = 0; i < size; i++)
				{
					scoring[6] += dice[i];
				}
			}
			else
			{
				scoring[6] = 0;
			}
			used[score - 1] = 1;
		}
		if (score == 8)
		{
			if (num1 == 4 || num2 == 4 || num3 == 4 || num4 == 4 || num5 == 4 || num6 == 4)
			{
				for (i = 0; i < size; i++)
				{
					scoring[7] += dice[i];
				}
			}
			else
			{
				scoring[7] = 0;
			}
			used[score - 1] = 1;
		}
		if (score == 9)
		{
			if ((num1 == 3) || (num2 == 3) || (num3 == 3) || (num4 == 3) || (num5 == 3) || (num6 == 3) &&
				(num1 == 2) || (num2 == 2) || (num3 == 2) || (num4 == 2) || (num5 == 2) || (num6 == 2))
			{
				scoring[8] = 25;
			}
			else
			{
				scoring[8] = 0;
			}
			used[score - 1] = 1;
		}
		if (score == 10)
		{
			if ((dice[0] == dice[1] - 1 && dice[1] == dice[2] - 1 && dice[2] == dice[3] - 1) ||
				(dice[1] == dice[2] - 1 && dice[2] == dice[3] - 1 && dice[3] == dice[4] - 1))
			{
				scoring[9] = 30;
			}
			else
			{
				scoring[9] = 0;
			}
			used[score - 1] = 1;
		}
		if (score == 11)
		{
			if (num1 == 1 && num2 == 1 && num3 == 1 && num4 == 1 && num5 == 1 && num6 == 1)
			{
				scoring[10] = 40;
			}
			else
			{
				scoring[10] = 0;
			}
			used[score - 1] = 1;
		}
		if (score == 12)
		{
			if (num1 == 5 || num2 == 5 || num3 == 5 || num4 == 5 || num5 == 5 || num6 == 5)
			{
				scoring[11] = 50;
			}
			else
			{
				scoring[11] = 0;
			}
			used[score - 1] = 1;
		}
		if (score == 13)
		{
			for (i = 0; i < size; i++)
			{
				scoring[12] += dice[i];
			}
			used[score - 1] = 1;
		}
	}
}

int * bubble_sort(int list[], int size)
{
	int index = 0, passes = 0, temp = 0;

	for (passes = 1; passes < size; ++passes)
	{
		for (index = 0; index < size - passes; ++index)
		{
			if (list[index] > list[index + 1])
			{
				temp = list[index];
				list[index] = list[index + 1];
				list[index + 1] = temp;
			}
		}
	}
	return list;
}

int add_up_score(int scoring[])
{
	int totscore = 0, upscore = 0, botscore = 0, bonus = 0,
		index = 0;

	for (index = 0; index < 6; ++index)
	{
		upscore += scoring[index];
	}
	
	for (index = 6; index < 13; ++index)
	{
		botscore += scoring[index];
	}

	if (upscore >= 63)
	{
		bonus = 35;
	}

	else
	{
		bonus = 0;
	}

	totscore = upscore + botscore + bonus;

	return totscore;
}

void print_final_score(int score1, int score2)
{
	printf("        FINAL SCORES        \n\n");
	printf("Player 1            Player 2\n");
	printf("   %d                  %d   \n\n", score1, score2);
	
	if (score1 > score2)
	{
		printf("        PLAYER 1\n         WINS\n");
	}
	if (score1 < score2)
	{
		printf("        PLAYER 2\n         WINS\n");
	}
	if (score1 == score2)
	{
		printf("        TIE\n");
	}
}