/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA3
Date: Febuary 8, 2017
Description: Processes numbers, corresponding to student records
			read in from a file, and writes the required results
			to an output file
*/

#include "header.h"

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

void run_app(void)
{
	int id1 = 0, id2 = 0, id3 = 0, id4 = 0, id5 = 0,
		class1 = 0, class2 = 0, class3 = 0, class4 = 0, class5 = 0;
	double gpa1 = 0.0, gpa2 = 0.0, gpa3 = 0.0, gpa4 = 0.0, gpa5 = 0.0,
		age1 = 0.0, age2 = 0.0, age3 = 0.0, age4 = 0.0, age5 = 0.0,
		gpasum = 0.0, classsum = 0.0, agesum = 0.0, meangpa = 0.0,
		meanclass = 0.0, meanage = 0.0, variance = 0.0,
		standard_deviation = 0.0, devgpa1 = 0.0, devgpa2 = 0.0,
		devgpa3 = 0.0, devgpa4 = 0.0, devgpa5 = 0.0, max = 0.0, min = 0.0;
	FILE *infile = NULL, *outfile = NULL;

	infile = fopen("input.dat", "r");
	outfile = fopen("output.dat", "w");

	if ((infile == NULL) || (outfile == NULL))
	{
		printf("Either could not open %s for reading or %s for writing!\n",
			"input.dat", "output.dat");
		printf("Exiting program!\n");
	}
	if((infile != NULL) && (outfile != NULL))
	{
		id1 = read_integer(infile);
		gpa1 = read_double(infile);
		class1 = read_integer(infile);
		age1 = read_double(infile);

		id2 = read_integer(infile);
		gpa2 = read_double(infile);
		class2 = read_integer(infile);
		age2 = read_double(infile);

		id3 = read_integer(infile);
		gpa3 = read_double(infile);
		class3 = read_integer(infile);
		age3 = read_double(infile);

		id4 = read_integer(infile);
		gpa4 = read_double(infile);
		class4 = read_integer(infile);
		age4 = read_double(infile);

		id5 = read_integer(infile);
		gpa5 = read_double(infile);
		class5 = read_integer(infile);
		age5 = read_double(infile);

		gpasum = calculate_sum(gpa1, gpa2, gpa3, gpa4, gpa5);
		classsum = calculate_sum(class1, class2, class3, class4, class5);
		agesum = calculate_sum(age1, age2, age3, age4, age5);

		meangpa = calculate_mean(gpasum, 5);
		meanclass = calculate_mean(classsum, 5);
		meanage = calculate_mean(agesum, 5);
		print_double(outfile, meangpa);
		print_double(outfile, meanclass);
		print_double(outfile, meanage);

		devgpa1 = calculate_deviation(gpa1, meangpa);
		devgpa2 = calculate_deviation(gpa2, meangpa);
		devgpa3 = calculate_deviation(gpa3, meangpa);
		devgpa4 = calculate_deviation(gpa4, meangpa);
		devgpa5 = calculate_deviation(gpa5, meangpa);
		variance = calculate_variance(devgpa1, devgpa2, devgpa3, devgpa4, devgpa5, 5);
		standard_deviation = calculate_standard_deviation(variance);
		print_double(outfile, standard_deviation);

		max = find_max(gpa1, gpa2, gpa3, gpa4, gpa5);
		min = find_min(gpa1, gpa2, gpa3, gpa4, gpa5);
		print_double(outfile, min);
		print_double(outfile, max);
	}
	
	fclose(infile);
	fclose(outfile);

	return 0;
}

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

double read_double(FILE *infile)
{
	double a = 0.0;
	
	fscanf(infile, "%lf", &a);

	return a;
}

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

int read_integer(FILE *infile)
{
	int b = 0;

	fscanf(infile, "%d", &b);

	return b;
}

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

double calculate_sum(double n1, double n2, double n3, double n4, double n5)
{
	double sum = 0.0;

	sum = n1 + n2 + n3 + n4 + n5;

	return sum;
}

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

double calculate_mean(double sum, int number)
{
	double mean = 0.0;

	if (number == 0)
	{
		mean = -1.0;
	}
	else
	{
		mean = sum / number;
	}

	return mean;
}

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

double calculate_deviation(double number, double mean)
{
	double dev = 0.0;

	dev = number - mean;

	return dev;
}

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

double calculate_variance(double dev1, double dev2, double dev3, double dev4, double dev5, int number)
{
	double variance = 0.0;

	variance = (pow(dev1, 2) + pow(dev2, 2) + pow(dev3, 2) + pow(dev4, 2) + pow(dev5, 2)) / number;

	return variance;
}

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

double calculate_standard_deviation(double variance)
{
	double standev = 0.0;

	standev = sqrt(variance);

	return standev;
}

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

double find_max(double n1, double n2, double n3, double n4, double n5)
{
	double max = 0.0;

	max = n1;

	if (n2 > max)
	{
		max = n2;
	}
	if (n3 > max)
	{
		max = n3;
	}
	if (n4 > max)
	{
		max = n4;
	}
	if (n5 > max)
	{
		max = n5;
	}

	return max;
}

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

double find_min(double n1, double n2, double n3, double n4, double n5)
{
	double min = 0.0;

	min = n1;

	if (n2 < min)
	{
		min = n2;
	}
	if (n3 < min)
	{
		min = n3;
	}
	if (n4 < min)
	{
		min = n4;
	}
	if (n5 < min)
	{
		min = n5;
	}

	return min;
}

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

void print_double(FILE *outfile, double number)
{
	fprintf(outfile, "%.2lf\n", number);
}