/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA6
Date: March 27, 2017
Description: Making a battleship game
*/

#ifndef PA6_HEADER_H
#define PA6_HEADER_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h> //rand(), srand()
#include <time.h>

typedef struct stats
{
	int total_hits;
	int total_misses;
	int total_shots;
	double hits_misses;
}Stats;

void welcome_screen(void);

void initialize_game_board(char playerboard[10][10]);

int select_who_starts_first();

int rand_index();

void manually_place_ships_on_board(char playerboard[10][10]);

void randomly_place_ships_on_board(char playerboard[10][10]);

int check_shot(char playerboard[10][10], int x, int y);

int is_winner(char playerboard[10][10]);

void update_board(char playerboard[10][10], int x, int y, int hit);

void display_board(char playerboard[10][10]);

int output_current_move(int x, int y, int hit, FILE *outfile);

void check_if_ship_sunk(char playerboard[10][10], char ship);

void output_stats();

#endif