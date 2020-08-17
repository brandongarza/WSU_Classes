/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA4
Date: Febuary 15, 2017
Description: Using loops to model a game of 'craps'
*/

#include "header.h"

int main(void)
{
	double bank_balance = 0.0, wager = 0.0;

	//call one time only!
	srand((unsigned int) time(NULL));

	print_game_rules();
	bank_balance = get_bank_balance();
	wager = get_wager_amount();
	wager = check_wager_amount(wager, bank_balance);

	run_app(bank_balance, wager);

	return 0;
}