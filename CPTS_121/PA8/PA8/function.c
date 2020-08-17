/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA8
Date: April 23, 2017
Description:
*/

#include "header.h"

//Part 1
void my_str_n_cat(char *destination_ptr, char *source_ptr)
{
	int i = 0, end = 0;

	end = strlen(destination_ptr);
	while (source_ptr[i] != '\0')
	{
		destination_ptr[i + end] = source_ptr[i];
		i++;
	}
}

//Part 2
//Precondition: list must be sorted
int binary_search(int sorted_list[], int size, int target)
{
	int left = 0, right = 0, targetindex = -1, found = 0, mid = 0;

	right = size - 1;
	while ((left <= right) && (found == 0))
	{
		mid = left + ((right - left) / 2);
		if (sorted_list[mid] == target)
		{
			found = 1;
			targetindex = mid;
		}
		if (sorted_list[mid] > target)
		{
			right = mid - 1;
		}
		if (sorted_list[mid] < target)
		{
			left = mid + 1;
		}
	}
	return targetindex;
}

//Part 3
void bubble_sort(char *list[], int strings)
{
	int start = 0, end = 0, i = 0, temp = 0;

	end = strings;

	for (i = 0; i < end; i++)
	{
		for (start = 1; start < end; start++)
		{
			if (strcmp(list[start], list[start - 1]) < 0)
			{
				temp = list[start];
				list[start] = list[start - 1];
				list[start - 1] = temp;
			}
		}
	}
}

//Part 4
int is_palindrome(char *word, int length)
{
	int i = 0, start = 0, end = 0;

	i = length / 2;
	end = length - 1;

	if (i == 0)
	{
		return 1;
	}
	else
	{
		if (*(word + start) == *(word + end))
		{
			is_palindrome((word + start + 1), length - 2);
		}
		else
		{
			return 0;
		}
	}
}

//Part 5
int sum_primes(int n, int start)
{
	int i = 0, result = 0, prime = 1;
	
	if (start > n)
	{
		return result;
	}
	else
	{
		for (i = 2; i < start; i++)
		{
			if (start % i == 0)
			{
				prime = 0;
			}
		}
		if (prime != 0 && start >= 2)
		{
			result = start + sum_primes(n, start + 1);
		}
		else
		{
			result = sum_primes(n, start + 1);
		}
	}
}

//Part 6
void max_occurrences(char *str, Occurrences *occ, int *frequency, char *character)
{
	int i = 0, j = 0, max_count = 0;
	char c = '\0';

	for (j = 0; j < strlen(str); j++)
	{
		c = str[j];
		occ[j].num_occurrences = 0;
		for (i = 0; i < strlen(str); i++)
		{
			if (c == str[i])
			{
				occ[j].num_occurrences++;
			}
			occ[j].frequency = occ[j].num_occurrences / strlen(str);
			if (occ[j].num_occurrences > max_count)
			{
				max_count = occ[j].num_occurrences;
				*frequency = max_count;
				*character = c;
			}
		}
	}
}

