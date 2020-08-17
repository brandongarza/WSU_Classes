/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA8
Date: April 23, 2017
Description:
*/

#include "header.h"

int main(void)
{
	char destination[100] = { '\0' }, source[100] = "Hello!";
	int list[10] = { 1,4,8,12,15,22,23,26,42,50 };
	char *charlist[] = { "brandon", "paulina", "joshua", "jorge" };
	char word[100] = "racecar";
	Occurrences occ[20];
	char *string = "Hello World";
	char character = '\0';
	int index = 0, palindrome = 0, sum = 0, frequency = 0;

	printf("PART 1\n");
	my_str_n_cat(destination, source);
	printf("%s\n", destination);

	printf("\nPART 2\n");
	index = binary_search(list, 10, 42);
	printf("%d\n", index);

	printf("\nPART 3\n");
	bubble_sort(charlist, 4);
	int i = 0;
	for (i = 0; i < 4; i++) 
	{
		printf("%s\n", charlist[i]);
	}

	printf("\nPART 4\n");
	palindrome = is_palindrome(word, 7);
	printf("%d\n", palindrome);

	printf("\nPART 5\n");
	sum = sum_primes(7, 2);
	printf("%d\n", sum);

	printf("\nPART 6\n");
	max_occurrences(string, occ, &frequency, &character);
	printf("%c occurs most at %d times\n\n", character, frequency);

	
	return 0;
}