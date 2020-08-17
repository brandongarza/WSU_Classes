/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA2
Date: Febuary 3, 2017
Description: Use three file format to solve various equations based on user input
*/

#pragma once
#include <stdio.h>
#include <math.h>

/********************************************************************
Function: calculate_newtons_2nd_law ()
Date Created: 2/1/2017
Date Last Modified:
Description: Takes input mass and acceleration and outputs a force
using newton's second law.
Input Parameters: Mass and acceleration
Returns: Force
Preconditions:
Postconditions
*********************************************************************/

double calculate_newtons_2nd_law(double mass, double acceleration);

/********************************************************************
Function: calculate_volume_cylinder ()
Date Created: 2/1/2017
Date Last Modified:
Description: Takes inputs radius and height and outputs the volume
of a cylinder using a volume equation
Input Parameters: radius and height of a cylinder
Returns: Volume of a cylinder
Preconditions:
Postconditions:
*********************************************************************/

double calculate_volume_cylinder(double radius, double height);

/********************************************************************
Function: perform_character_encoding ()
Date Created: 2/1/2017
Date Last Modified:
Description: Takes an input character and changes it into the
capitalized version of it.
Input Parameters: A character
Returns: A capitalized version of the input character.
Preconditions:
Postconditions
*********************************************************************/

char perform_character_encoding(char plaintext_character);

/********************************************************************
Function: calculate_gauss_lens ()
Date Created: 2/1/2017
Date Last Modified:
Description: Takes an input of object distance and image distance
and uses the gauss law of lenses equation to calculate
focal length.
Input Parameters: Object distance and image distance
Returns: Focal length
Preconditions:
Postconditions
*********************************************************************/

double calculate_gauss_lens(double obdist, double imdist);

/********************************************************************
Function: calculate_tangent ()
Date Created: 2/1/2017
Date Last Modified:
Description: Takes input of theta and calculates the tangent of the
given angle theta
Input Parameters: Theta
Returns: Tangent of angle theta
Preconditions:
Postconditions
*********************************************************************/

double calculate_tangent(double theta);

/********************************************************************
Function: calculate_resistive_divider ()
Date Created: 2/1/2017
Date Last Modified:
Description: Takes inputs of resistance for two resistors and the
voltage in and uses the voltage divider equation for circuits
to calculate the voltage out.
Input Parameters: Resistance for the two resistors and voltage in
Returns: Voltage out
Preconditions:
Postconditions
*********************************************************************/

double calculate_resistive_divider(double r1, double r2, double vin);

/********************************************************************
Function: calculate_distance_between_2pts ()
Date Created: 2/1/2017
Date Last Modified:
Description: Takes input of two cartesian points and calculates the
distance between them.
Input Parameters: Two points
Returns: Distance between points
Preconditions:
Postconditions
*********************************************************************/

double calculate_distance_between_2pts(double x1, double y1, double x2, double y2);

/********************************************************************
Function: calculate_general_equation ()
Date Created: 2/1/2017
Date Last Modified:
Description: Calculates the result of the general equation given inputs
a, x, and z
Input Parameters: Values for the variables a, x, and z
Returns: Result of equation y
Preconditions:
Postconditions
*********************************************************************/

double calculate_general_equation(int a, double x, double z);
