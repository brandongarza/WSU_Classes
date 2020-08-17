/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA4
Date: Febuary 15, 2017
Description: Using loops to model a game of 'craps'
*/

#include "header.h"

void run_app(double bank_balance, double wager)
{
	int die1 = 0, die2 = 0, sum = 0, sum2 = 0, point_value = 0,
		win_loss = 0, result = 0, number_rolls = 1;
	double add_wager = 0.0, current_bank_balance = 0.0, total_wager = 0.0;

	die1 = roll_die();
	die2 = roll_die();
	printf("die1: %d\n", die1);
	printf("die2: %d\n", die2);
	sum = sum_dice(die1, die2);
	printf("sum: %d\n", sum);

	current_bank_balance = bank_balance - wager;

	chatter_messages(number_rolls, bank_balance, current_bank_balance);

	win_loss = is_win_loss_or_point(sum);

	if (win_loss == 1)
	{
		bank_balance = adjust_bank_balance(bank_balance, wager, win_loss);
		printf("You have won.\n", wager);
	}
	if (win_loss == 0)
	{
		bank_balance = adjust_bank_balance(bank_balance, wager, win_loss);
		printf("You have lost.\n", wager);
	}
	if (win_loss == -1)
	{
		while (win_loss == -1)
		{
			printf("Enter additional wager: ");
			scanf("%lf", &add_wager);
			wager += add_wager;
			wager = check_wager_amount(wager, bank_balance);
			current_bank_balance = bank_balance - wager;
			total_wager += wager;

			printf("Roll again!\n");
			die1 = roll_die();
			die2 = roll_die();
			printf("die1: %d\n", die1);
			printf("die2: %d\n", die2);

			sum2 = sum_dice(die1, die2);
			printf("sum: %d\n", sum2);
			win_loss = is_point_loss_or_neither(sum2, sum);

			number_rolls += 1;

			current_bank_balance = bank_balance - wager;
			chatter_messages(number_rolls, bank_balance, current_bank_balance);
		}
		if (win_loss == 1)
		{
			current_bank_balance = adjust_bank_balance(bank_balance, total_wager, win_loss);
			printf("You have won");
			chatter_messages(number_rolls, bank_balance, current_bank_balance);

		}
		if (win_loss == 0)
		{
			current_bank_balance = adjust_bank_balance(bank_balance, total_wager, win_loss);
			printf("You have lost\n");
			chatter_messages(number_rolls, bank_balance, current_bank_balance);
		}
	}
}

void print_game_rules(void)
{
	printf("A player rolls two dice. Each die has six faces.\n");
	printf("faces contain 1, 2, 3, 4, 5, and 6 spots. After\n");
	printf("the dice have come to rest, the sum of the spots on the\n");
	printf("two upward faces is calculated.If the sum is 7 or 11 on\n");
	printf("the first throw, the player wins.If the sum is 2, 3, or\n");
	printf("12 on the first throw (called 'craps'), the player loses\n");
	printf("(i.e.the 'house' wins).If the sum is 4, 5, 6, 8, 9, or 10\n");
	printf("'point.' To win, you must continue rolling the dice until\n");
	printf("you 'make your point.' The player loses by rolling a 7\n");
	printf("before making the point.\n\n");
}

double get_bank_balance(void)
{
	double balance = 0.0;

	printf("Enter bank balance: ");
	scanf("%lf", &balance);
	printf("Bank Balance = %.2lf\n", balance);
	
	return balance;
}

double get_wager_amount(void)
{
	double wager = 0.0;

	printf("Enter wager: ");
	scanf("%lf", &wager);

	return wager;
}

double check_wager_amount(double wager, double balance)
{
	while (((wager > balance) & (wager != balance)) | (wager < 0))
	{
		printf("Insufficient funds. %.2lf available\n", balance);
		wager = get_wager_amount();
	}
	printf("Acceptable wager: %.2lf\n", wager);
	return wager;
}

int roll_die(void)
{
	int die = 0;

	die = rand() % 6 + 1;

	return die;
}

int sum_dice(int die1, int die2)
{
	int sum = 0;

	sum = die1 + die2;

	return sum;
}

int is_win_loss_or_point(int sum_dice)
{
	if ((sum_dice == 7) | (sum_dice == 11))
	{
		return 1;
	}
	if ((sum_dice == 2) | (sum_dice == 3) | (sum_dice == 12))
	{
		return 0;
	}
	return -1;
}

int is_point_loss_or_neither(int sum_dice, int point_value)
{
	if (sum_dice == point_value)
	{
		return 1;
	}
	if (sum_dice == 7)
	{
		return 0;
	}
	return -1;
}

double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract)
{
	if (add_or_subtract == 1)
	{
		bank_balance = bank_balance + wager_amount;
	}
	if (add_or_subtract == 0)
	{
		bank_balance = bank_balance - wager_amount;
	}

	return bank_balance;
}

void chatter_messages(int number_rolls, double initial_bank_balance, double current_bank_balance)
{
	printf("Number of rolls: %d\n", number_rolls);
	printf("Initial bank balance: %.2lf\n", initial_bank_balance);
	printf("Current bank balance; %.2lf\n\n", current_bank_balance);
}