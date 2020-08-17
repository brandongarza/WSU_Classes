/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA7
Date: April 12, 2017
Description: Making a poker game
*/

#ifndef PA7_HEADER_H
#define PA7_HEADER_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h> //rand(), srand()
#include <time.h>

void shuffle (int wDeck[][13]);

void deal(const int wDeck[][13], const char *wFace[], const char *wSuit[]);

void is_pair();

void is_two_pair();

void is_three_of_a_kind();

void is_four_of_a_kind();

void is_straight();

void is_flush();


#endif