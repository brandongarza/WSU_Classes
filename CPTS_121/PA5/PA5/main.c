/*Programmer: Brandon Garza/"*
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA5
Date: Febuary 24, 2017
Description: Making a yahtzee
*/

#include "header.h"

int main(void)
{
	int dice[5] = {0}, scoring[13] = {0}, used[13] = {0}, 
		scoring2[13] = {0}, used2[13] = {0},
		a = 0, sizedice = 5, numrolls = 1, numrolls2 = 1, 
		score = 0, turn = 0, num1 = 0, num2 = 0, num3 = 0,
		num4 = 0, num5 = 0, num6 = 0;
	int * dice_ptr = NULL;
	char yesno = '\0';

	srand((unsigned int)time(NULL));

	do
	{
		printf("1. Print game rules\n2. Start game of yahtzee\n3. Exit\n");
		scanf("%d", &a);
		if (a == 1)
		{
			system("cls");
			printf("The scorecard used for Yahtzee is composed of two sections. An upper section and a lower section.\n");
			printf("A total of thirteen boxes or thirteen scoring combinations are divided amongst the sections.\n");
			printf("The upper section consists of boxes that are scored by summing the value of the dice matching the faces of the box.\n");
			printf("If a player rolls four 3's, then the score placed in the 3's box is the sum of the dice which is 12.\n");
			printf("Once a player has chosen to score a box, it may not be changed and the combination is no longer in play for future rounds.\n");
			printf("If the sum of the scores in the upper section is greater than or equal to 63, then 35 more points are added\n");
			printf("to the players overall score as a bonus.The lower section contains a number of poker like combinations.\n");
			printf("See the table provided below: \n\n");
			printf("Ones            -> sum of all ones\n");
			printf("Twos            -> sum of all twos\n");
			printf("Threes          -> sum of all threes\n");
			printf("Fours           -> sum of all fours\n");
			printf("Fives           -> sum of all fives\n");
			printf("Sixes           -> sum of all sixes\n");
			printf("Three-of-a-kind -> sum of all dice\n");
			printf("Four-of-a-kind  -> sum of all dice\n");
			printf("Full house      ->        25\n");
			printf("Small straight  ->        30\n");
			printf("Large straight  ->        40\n");
			printf("Yahtzee         ->        50\n");
			printf("Chance          -> sum of all dice\n\n");
		}
	} while ((a != 2) && (a != 3));

	if (a == 3)
	{
		system("cls");
		printf("Goodbye\n");
	}
	if (a == 2)
	{
		while (turn < 14)
		{
			//1st player
			printf("1st player hit ENTER to continue: \n");
			getch();
			system("cls");
			roll_dice1(dice, sizedice);
			do
			{
				printf("Do you want to keep combination? (y or n): \n");
				scanf(" %c", &yesno);

				if (yesno == 'n')
				{
					reroll_dice(dice, sizedice);
					++numrolls;
				}
			} while ((yesno == 'n') && (numrolls < 3));

			if ((yesno == 'y') || (numrolls >= 3))
			{
				count_die_values(dice, sizedice, &num1, &num2, &num3,
					&num4, &num5, &num6);
				printf("%d %d %d %d %d\n", num1, num2, num3, num4, num5, num6);
				dice_ptr = bubble_sort(dice, sizedice);
				print_score_card(scoring);
				printf("Choose hand to get points: ");
				scanf("%d", &score);
				system("cls");

				check_score(dice, scoring, used, sizedice, score,
					num1, num2, num3, num4, num5, num6);
				print_score_card(scoring);
			}

			//2nd player
			printf("2nd player hit ENTER to continue: \n");
			getch();
			system("cls");
			roll_dice1(dice, sizedice);
			do
			{
				printf("Do you want to keep combination? (y or n): \n");
				scanf(" %c", &yesno);

				if (yesno == 'n')
				{
					reroll_dice(dice, sizedice);
					++numrolls2;
				}
			} while ((yesno == 'n') && (numrolls2 < 3));

			if ((yesno == 'y') || (numrolls2 >= 3))
			{
				count_die_values(dice, sizedice, &num1, &num2, &num3,
					&num4, &num5, &num6);
				dice_ptr = bubble_sort(dice, sizedice);
				print_score_card(scoring2);
				printf("Choose hand to get points: ");
				scanf("%d", &score);
				system("cls");

				check_score(dice, scoring2, used2, sizedice, score,
					num1, num2, num3, num4, num5, num6);
				print_score_card(scoring2);
			}
			++turn;
		}
		print_final_score(add_up_score(scoring), add_up_score(scoring2));
	}
	return 0;
}