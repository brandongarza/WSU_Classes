/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA8
Date: April 23, 2017
Description: 
*/

#ifndef PA7_HEADER_H
#define PA7_HEADER_H

#pragma once
#include <stdio.h>
#include <math.h>
#include <stdlib.h> //rand(), srand()
#include <time.h>
#include <string.h>

typedef struct occurrences
{
	int num_occurrences;
	double frequency;
} Occurrences;

void my_str_n_cat(char *destination_ptr, char *source_ptr);

int binary_search(int sorted_list[], int size, int target);

void bubble_sort(char *list[], int strings);

int is_palindrome(char *word, int length);

int sum_primes(int n, int start);

void max_occurrences(char *str, Occurrences *occ, int *frequency, char *character);





#endif