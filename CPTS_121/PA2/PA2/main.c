/*Programmer: Brandon Garza
Class: CptS 121, Spring 2017; Lab Section 10
Programming Assignment: PA2
Date: Febuary 3, 2017
Description: Use three file format to solve various equations based on user input
*/

#include "Header.h"

int main(void)
{
	double mass = 0.0, accel = 0.0, force = 0.0, radius = 0.0, height = 0.0, volume = 0.0,
		obdist = 0.0, imdist = 0.0, focleng = 0.0, theta = 0.0, tan_theta = 0.0, r1 = 0.0,
		r2 = 0.0, vin = 0.0, vout = 0.0, x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0, dist = 0.0,
		b = 0.0, x = 0.0, z = 0.0, y = 0.0;
	int a = 0;
	char plain_text = 's', encoded_character = 'd';

	//1 - Newtons second law
	printf("Newtons Second Law\n");
	printf("Enter mass of object <floating point value>: ");
	scanf("%lf", &mass);
	printf("Enter acceleration of object <floating point value>: ");
	scanf("%lf", &accel);
	force = calculate_newtons_2nd_law(mass, accel);
	printf("mass * acceleration = force: %.2lf * %.2lf = %.2lf\n", mass, accel, force);

	//2 - equation for volume of a cylinder
	printf("Volume of a cylinder\n");
	printf("Enter radius of cylinder <floating point value>: ");
	scanf("%lf", &radius);
	printf("Enter height of cylinder <floating point value>: ");
	scanf("%lf", &height);
	volume = calculate_volume_cylinder(radius, height);
	printf("pi * radius^2 * height = volume: 3.1415 * %.2lf^2 * %.2lf = %.2lf\n", radius, height, volume);

	//3 - characters
	printf("Character encoder\n");
	printf("Enter a plain text character: ");
	scanf(" %c", &plain_text);
	encoded_character = perform_character_encoding(plain_text);
	printf("plain text character - 'a' + 'A' = encoded character: %c - 'a' + 'A' = %c\n", plain_text, encoded_character);

	//4 - Gauss lens formula
	printf("Gauss lens formula\n");
	printf("Enter the object distance and image distance: ");
	scanf("%lf%lf", &obdist, &imdist);
	focleng = calculate_gauss_lens(obdist, imdist);
	printf("1/(1/object distance + 1/image distance) = focal length: 1/(1/%.2lf + 1/%.2lf) = %.2lf\n", obdist, imdist, focleng);

	//5 - tangent
	printf("Tanget of angle theta\n");
	printf("Enter the angle in radians: ");
	scanf("%lf", &theta);
	tan_theta = calculate_tangent(theta);
	printf("sin(theta) / cos(theta) = tan(theta): sin(%.2lf) / cos(%.2lf) = %.2lf\n", theta, theta, tan_theta);

	//6 - resistive divider
	printf("Resistive divider\n");
	printf("Enter the first and second resistance and the voltage in: ");
	scanf("%lf%lf%lf", &r1, &r2, &vin);
	vout = calculate_resistive_divider(r1, r2, vin);
	printf("r2 / (r1 + r2) * vin = vout: %.2lf / (%.2lf + %.2lf) * %.2lf = %.2lf\n", r2, r1, r2, vin, vout);

	//7 - distance between two points
	printf("Distance between two points\n");
	printf("Enter two points (x1, y1) and (x2, y2): ");
	scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
	dist = calculate_distance_between_2pts(x1, y1, x2, y2);
	printf("sqrt ((x1-x2)^2 + (y1-y2)^2) = distance: sqrt ((%.2lf-%.2lf)^2 + (%.2lf-%.2lf)^2) = %.3lf\n", x1, x2, y1, y2, dist);

	//8 - General equation
	printf("Enter values for a, x, and z: ");
	scanf("%d%lf%lf", &a, &x, &z);
	b = 63.0 / -17.0;
	y = calculate_general_equation(a, x, z);
	printf("a / (a mod 2) - (63 / -17) + x * z = y: %d / (%d mod 2) - (63 / -17) + %.2lf * %.2lf = %.2lf", a, a, x, z, y);
	
	return 0;
}