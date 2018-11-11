#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main ()
{
	/* This program will produce a table with the value of the volume of a cone
	 * with heights of 1, 7, 9, and 15 cms starting at a user designated diameter
	 * and increments of diameter also designated by the user.
	 * 
	 * Written by Jayden Cole and Ryan Stolys
	 * Date: 2017-10-30
	 */

	// Declare and initialize variables
		
	double diameterCone = 0.0;			//Inputs from the user
	int numberOfRows = 0;
	double diamInterval = 0.0;
	
	int inputAttempts = 1;				//Counter for number of attempts made at inputs

	int rowNumber = 1;					//Row number

	double volumeOfH1 = 0.0;			//Volumes that will be calculated and displayed in the table
	double volumeOfH7 = 0.0;
	double volumeOfH9 = 0.0;
	double volumeOfH15 = 0.0;

	int diamterCheck = 0;				//These check variables will be the test for the input loops
	int rowCheck = 0;					// to determine if they have been completed.
	int intervalCheck = 0;



	// Declare and set constants

	const double PI = 3.14159265;			//Constants used in the	calculation of volume
	const double VOLUME_DIVISOR = 12.0;

	int const MAX_ATTEMPTS = 3;			//Constant used to measure the maximum number of attempts user has to input correct info
	
	const double MIN_DIAMETER = 0.000;		//Range that inputs must be within
	const double MAX_DIAMETER = 60.000;

	const int MIN_ROWS = 1;				//Range that inputs must be within
	const int MAX_ROWS = 23;

	const double MIN_INTERVAL = 0.1;			//Range that inputs must be within
	const double MAX_INTERVAL = 5.0;

	const int COLUMN_WIDTH = 15;			//Widths of Columns in Table

	const int MAX_TABLE_DIAMETER = 120;		//Upper limit that table will display values for diameter and calculated volumes

	const int HEIGHT1 = 1;					//Heights used in calculations to get their respective volumes
	const int HEIGHT7 = 7;
	const int HEIGHT9 = 9;
	const int HEIGHT15 = 15;

	//Prompt user for inputs 

	while (diamterCheck == 0)
	{
		//Prompt user for starting diameter of cone
		cout<<"enter the diameter of the base of the cone for the first row"<<endl;
		cout<<fixed<<setprecision(3)<<MIN_DIAMETER<<" <= x <= "<<MAX_DIAMETER<<" ";
		cin>>diameterCone;

		if (MIN_DIAMETER > diameterCone || MAX_DIAMETER < diameterCone)								//See if the diameter is within the set boundaries
		{
			if (inputAttempts >= MAX_ATTEMPTS)														//See if the user has more attempts to imput diameter within boundaries																						
			{
				cout<<"Exceeded number of tries reading the initial diameter of the cone"<<endl;
				cout<<"Program is terminating";
				return 0;
			}
			cout<<" You entered "<<diameterCone<<endl;
			cout<<"TRY AGAIN PLEASE"<<endl;
			inputAttempts++;
			continue;
		}
		inputAttempts = 1;		//Reset of attemps counter
		diamterCheck = 1;		//Indicate diameter has been successfully inputed
	}

	while (rowCheck == 0)
	{
		//Ask user for number of rows
		cout<<"enter the number of rows in the table "<<MIN_ROWS<<" <= x <= "<<MAX_ROWS<<" ";
		cin>>numberOfRows;
		if (MIN_ROWS > numberOfRows || MAX_ROWS < numberOfRows)
		{
			if (inputAttempts >= MAX_ATTEMPTS)
			{
				cout<<"Exceeded number of tries reading the number of rows"<<endl;
				cout<<"Program is terminating";
				return 0;
			}
			cout<<" You entered "<<numberOfRows<<endl;
			cout<<"TRY AGAIN PLEASE"<<endl;
			inputAttempts++;
			continue;
		}
		inputAttempts = 1;			//Reset input attempts for next variable
		rowCheck = 1;				//Means number of rows has been correctly inputted
	}

	while (intervalCheck == 0)
	{
		//Ask user for interval of diameter for table
		cout<<"enter the length of the interval between entries in the table"<<endl;
		cout<<MIN_INTERVAL<<" <= diamInterval <= "<<MAX_INTERVAL<<" ";
		cin>>diamInterval;
		if (MIN_INTERVAL > diamInterval || MAX_INTERVAL < diamInterval)				//Check if interval is between 0.1 and 5
		{
			if (inputAttempts >= MAX_ATTEMPTS)										//Check is user has had three attempts to input interval
			{
				cout<<"Exceeded number of tries reading the interval"<<endl;
				cout<<"Program is terminating";
				return 0;
			}
			cout<<" You entered "<<diamInterval<<endl;
			cout<<"TRY AGAIN PLEASE"<<endl;
			inputAttempts++;
			continue;
		}
		inputAttempts = 1;
		intervalCheck = 1;
	}

	//Display Table headings

	cout << endl << endl ;						//Positions headings on correct line
	cout << setw (COLUMN_WIDTH) << "Diameter";
	cout << setw (COLUMN_WIDTH) << "Volume for";
	cout << setw (COLUMN_WIDTH) << "Volume for";
	cout << setw (COLUMN_WIDTH) << "Volume for";
	cout << setw (COLUMN_WIDTH) << "Volume for" << endl;

	cout << setw (COLUMN_WIDTH) << " ";
	cout << setw (COLUMN_WIDTH) << "height 1cm";
	cout << setw (COLUMN_WIDTH) << "height 7cm";
	cout << setw (COLUMN_WIDTH) << "height 9cm";
	cout << setw (COLUMN_WIDTH) << "height 15cm" << endl;


	//Display numerical values in table

	for (rowNumber = 1; numberOfRows > 0; numberOfRows--, diameterCone -= diamInterval * (rowNumber - 1) /*reset diameterCone to inputted value*/, rowNumber++)
	{
		//Calculate diameter value for this row
		diameterCone += diamInterval * (rowNumber - 1);

		//Check if diameter is not too large to be displayed
		if (diameterCone >= 120)
		{
			cout << "diameter of cone exceeded the maximum value allowed, line not printed";
			cout << endl;
			continue;
		}
		

		//Calculate volumes

		volumeOfH1 = PI * diameterCone * diameterCone * HEIGHT1 / VOLUME_DIVISOR;
		volumeOfH7 = PI * diameterCone * diameterCone * HEIGHT7 / VOLUME_DIVISOR;
		volumeOfH9 = PI * diameterCone * diameterCone * HEIGHT9 / VOLUME_DIVISOR;
		volumeOfH15 = PI * diameterCone * diameterCone * HEIGHT15 / VOLUME_DIVISOR;
		
		//Display diameter and volumes
		
		cout << setw(COLUMN_WIDTH) << diameterCone;
		cout << setw(COLUMN_WIDTH) << volumeOfH1;
		cout << setw(COLUMN_WIDTH) << volumeOfH7;
		cout << setw(COLUMN_WIDTH) << volumeOfH9;
		cout << setw(COLUMN_WIDTH) << volumeOfH15 << endl;
	}
	return 0;
}