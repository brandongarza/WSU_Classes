/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA3
Date: Febuary 8, 2017
Description: Processes numbers, corresponding to student records
read in from a file, and writes the required results
to an output file
*/

#ifndef PA3_HEADER_H
#define PA3_HEADER_H

#include <stdio.h>
#include <math.h>

/********************************************************************
Function: run_app()
Date Created: 2/8/2017
Date Last Modified:
Description: Opens input and output file.  Then calcualates mean GPA,
mean class rank, mean age, standard deviation of the GPA,
minimum GPA, and maximum GPA.  Next the values are output
into an output file.  Finally the files are closed.
Input Parameters: Nothing
Returns: Nothing
Preconditions:
Postconditions
*********************************************************************/

void run_app(void);

/********************************************************************
Function: read_double()
Date Created: 2/8/2017
Date Last Modified:
Description: Reads a double type value from an input file, copies
the value to a variable, and outputs the value
Input Parameters: Integer from input file
Returns: Value of double variable
Preconditions:
Postconditions
*********************************************************************/

double read_double(FILE *infile);

/********************************************************************
Function: read_integer()
Date Created: 2/8/2017
Date Last Modified:
Description: Reads a integer type value from an input file, copies
the value to a variable, and outputs the value
Input Parameters: Integer from input file
Returns: Value of integer variable
Preconditions:
Postconditions
*********************************************************************/

int read_integer(FILE *infile);

/********************************************************************
Function: calculate_sum()
Date Created: 2/8/2017
Date Last Modified:
Description: Calculates the sum of five double input values
Input Parameters: Five double values
Returns: The sum of the five values
Preconditions:
Postconditions
*********************************************************************/

double calculate_sum(double n1, double n2, double n3, double n4, double n5);

/********************************************************************
Function: calculate_mean()
Date Created: 2/8/2017
Date Last Modified:
Description: Calculates the mean of a sum of values
Input Parameters: The sum of the input values and the number of values
Returns: The mean of the values
Preconditions:
Postconditions
*********************************************************************/

double calculate_mean(double sum, int number);

/********************************************************************
Function: calculate_deviation()
Date Created: 2/8/2017
Date Last Modified:
Description: Calculates the deviation of a value from the mean of
those values
Input Parameters: A value and the mean of the group of values it
belongs to
Returns: The deviation of the value
Preconditions:
Postconditions
*********************************************************************/

double calculate_deviation(double number, double mean);

/********************************************************************
Function: calculate_variance()
Date Created: 2/8/2017
Date Last Modified:
Description: Calculates the variance of a set of five double values
Input Parameters: Five values and the number five
Returns: The variance of the five values
Preconditions:
Postconditions
*********************************************************************/

double calculate_variance(double dev1, double dev2, double dev3, double dev4, double dev5, int number);

/********************************************************************
Function: calculate_standard_deviation()
Date Created: 2/8/2017
Date Last Modified:
Description: Calculates the standard deviation from a variance
Input Parameters: The variance of a set of values
Returns: The standard deviation of the values
Preconditions:
Postconditions
*********************************************************************/

double calculate_standard_deviation(double variance);

/********************************************************************
Function: find_max()
Date Created: 2/8/2017
Date Last Modified:
Description: Determines the maximum value out of five values
Input Parameters: Five double type values
Returns: The maximum value out of the five
Preconditions:
Postconditions
*********************************************************************/

double find_max(double n1, double n2, double n3, double n4, double n5);

/********************************************************************
Function: find_min()
Date Created: 2/8/2017
Date Last Modified:
Description: Determines the minimum value out of five values
Input Parameters: Five double type values
Returns:The minimum value out of the five
Preconditions:
Postconditions
*********************************************************************/

double find_min(double n1, double n2, double n3, double n4, double n5);

/********************************************************************
Function: print_double()
Date Created: 2/8/2017
Date Last Modified:
Description: Prints a value to an output file
Input Parameters: A value
Returns: Nothing
Preconditions:
Postconditions
*********************************************************************/

void print_double(FILE *outfile, double number);

#endif
