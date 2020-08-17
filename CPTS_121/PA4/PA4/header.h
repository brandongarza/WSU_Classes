/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA4
Date: Febuary 15, 2017
Description: Using loops to model a game of 'craps'
*/

#ifndef PA4_HEADER_H
#define PA4_HEADER_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h> //rand(), srand()
#include <time.h>

/********************************************************************
Function: 
Date Created: 2/15/2017
Date Last Modified:
Description:
Input Parameters: 
Returns: 
Preconditions:
Postconditions
*********************************************************************/

void run_app(double bank_balance, double wager);

void print_game_rules(void);

double get_bank_balance(void);

double get_wager_amount(void);

double check_wager_amount(double wager, double balance);

int roll_die(void);

int sum_dice(int die1, int die2);

int is_win_loss_or_point(int sum_dice);

int is_point_loss_or_neither(int sum_dice, int point_value);

double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract);

void chatter_messages(int number_rolls, double initial_bank_balance, double current_bank_balance);

#endif