/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA7
Date: April 12, 2017
Description: Making a poker game
*/

#include "header.h"

int main(void)
{
	const char *suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	const char *face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six",
					"Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	int deck[4][13] = { 0 };
	
	srand((unsigned)time(NULL));

	shuffle(deck);
	deal(deck, face, suit);
	
	return 0;
}