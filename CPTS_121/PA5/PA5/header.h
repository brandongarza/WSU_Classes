/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA5
Date: Febuary 24, 2017
Description: Making a yahtzee
*/

#ifndef PA4_HEADER_H
#define PA4_HEADER_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h> //rand(), srand()
#include <time.h>

int roll_die(void);

void roll_dice1(int dice[], int max_items);

void reroll_dice(int dice[], int size);

void print_score_card(int scorecard[]);

void count_die_values(int dice[], int size, int *one_ptr, int *two_ptr,
	int *three_ptr, int *four_ptr, int *five_ptr, int *six_ptr);

void check_score(int dice[], int scoring[], int used[], int size, int score,
	int num1, int num2, int num3, int num4, int num5, int num6);

int * bubble_sort(int list[], int size);

int add_up_score(int scoring[]);

void print_final_score(int score1, int score2);

#endif