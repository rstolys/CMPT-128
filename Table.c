#include <stdio.h>
#include <math.h>
#pragma warning(disable: 4996)

/* 
	Author: Ryan Stolys
	Created on: Oct 24, 2017
	This program will ask a user for inputs about a table such as min and max x values and the number of rows in the table
	The program will produce this table with the outputs for x , sin3Tx error1 cost3Tx error2, sin3T2x  and error3
*/

int main ()
{
	/* Define Varaiables*/
	double xMin = 0.0;
	double xMax = 0.0;
	int numRows = 0;
	double xInterval = 0.0;

	/*Define and set Constants */
	double const MIN_X = -1.0;
	double const MAX_X = 1.0;
	int const MAX_ROWS = 27;
	int const MIN_ROWS = 3;
	int const VALUE_COSX_CONST = 1;

	/*Attempt Variables*/
	int rowAttempts = 0;
	int const MAX_ROW_ATTEMPTS = 3;

	/*Table Value Variables */
	double valueOfSinX = 0.0;
	double valueOfCosX = 0.0;
	double valueOfSin2x = 0.0;
	double error1 = 0.0;
	double error2 = 0.0;
	double error3 = 0.0;
	double xUse = 0.0;
	double sinX = 0.0;
	double cosX = 0.0;
	double sin2X = 0.0;

	/*Ask user for inputs and check values are within range */
	do
	{
		do
		{
			if (xMin < MIN_X || xMin > MAX_X)
			{
				printf("You entered a value  of xMin that was out of range, Try again\n");
			}

			printf("enter xMin, the smallest x used in the table  %.3lf < x <   %.3lf\n", MIN_X, MAX_X);
			scanf("%lf", &xMin);
		}
		while (xMin < MIN_X || xMin > MAX_X);

		do 
		{
			if (xMax < MIN_X || xMax > MAX_X)
			{
				printf("You entered a value  of xMax that was out of range, Try again\n");
			}

			printf("enter xMax, the largest x used in the table  %.3lf < x <   %.3lf\n", MIN_X, MAX_X);
			scanf("%lf", &xMax);
		}
		while (xMax < MIN_X || xMax > MAX_X);

		if (xMin > xMax)
		{
			printf("You entered a minimum limit larger than your maximum!  Try Again\n");
		}
	}
	while (xMin > xMax);

		do
		{
			printf("Enter the number of rows in the table (an integer) ");
			scanf("%d", &numRows);

			if (numRows < MIN_ROWS || numRows > MAX_ROWS)
			{
				if (rowAttempts >= MAX_ROW_ATTEMPTS)
				{
					printf("You have exceed the number of tries for entering number of rows, exiting");
					return 0;
				}
				printf("You entered a value  of number of rows that was out of range, Try again\n");
				rowAttempts++;
			}
		}
		while (numRows < MIN_ROWS || numRows > MAX_ROWS);


	/*Calculate the interval of the tables x values*/
	xInterval = (xMax - xMin)/(numRows - 1);


	/*Print Table headings */
	printf("%9s%10s%13s%10s%13s%10s%13s", "X", "sin3T(x)", "error1", "cos3T(x)", "error2", "sin3T(2x)", "error3");
	printf("\n");

	/*set inital x Value */
	xUse = xMin;

	/*Create Table*/ 
	while (xUse <= xMax)
	{
		/*Calculate Values */
		sinX = sin(xUse);
		valueOfSinX = (xUse) - ((pow(xUse,3))/(6)) + ((pow(xUse, 5))/(120)); 
		error1 = sinX - valueOfSinX;
		cosX = cos(xUse);
		valueOfCosX = VALUE_COSX_CONST - ((pow(xUse, 2))/(2)) + ((pow(xUse, 4))/(24));
		error2 = cosX - valueOfCosX;
		sin2X = sin(2*xUse);
		valueOfSin2x = 2*valueOfSinX*valueOfCosX;
		error3 = sin2X - valueOfSin2x;

		/*Print table output */
		printf("%9.5lf%10.5lf%13.4e%10.5lf%13.4e%10.5lf%13.4e", xUse, valueOfSinX, error1, valueOfCosX, error2, valueOfSin2x, error3);
		printf("\n");

		/*Increment xuse */
		xUse += xInterval;
	}

	return 0;
}