#include <iostream>
#include <fstream>
#include<stdlib.h>
#include <iomanip>
using namespace std;

//This program will as for user input to determine the name of an output file, seeds and min and max array values
//The program will call various functions to plot the points of the array, generate a 2D array and Count the number of Xs
//
//Created by Ryan Stolys
//Created on: 11/21/2017

int const MAX_ARRAY_SIZE = 30;

//Function Prototypes
void Generate2D(int random2D[][MAX_ARRAY_SIZE], int numberCols, int numberRows, int seed, int minValue, int maxValue);
void PointPlot(int scatterData[][MAX_ARRAY_SIZE], int rowLength, int columnLength, ostream& outstream);
int countXs(int scatterData[][MAX_ARRAY_SIZE], int rowLength, int columnLength);


int main ()
{
	int seed1 = 0;
	int seed2 = 0;
	char fileName[1024] = {'\0'};
	ofstream outFile; 
	int numRows = 0;
	int numCols = 0;
	int maxInt = 0;
	int minInt = 0;
	int tries = 0;
	int numOfX = 0;
	bool breakFlag = false;
	int const MAX_TRIES = 3;
	int const MIN_RAND_INT = 1;
	int const MAX_RAND_INT = 50;
	int plotArray[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = {0};
	int plotArray1[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = {0};
	int plotArray2[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = {0};

	//Initalize Arrays
	for (int a = 0; a < MAX_ARRAY_SIZE; a++)
	{
		for (int  g = 0; g < MAX_ARRAY_SIZE; g++)
		{
			plotArray[a][g] = -1000;
		} 
	}

	//Prompt user for file name
	cout<<"Please enter the name of the output file: ";
	cin>>fileName;

	//Open file
	outFile.open(fileName);

	//Check if file opened
	if (outFile.fail())
	{
		cerr<<"ERROR: unable to open file";
		return 0;
	}

	//Prompt for number of rows
	while (tries <= MAX_TRIES && breakFlag == false)
	{
		cout<<"Please enter the number of rows in the input arrays: "<<endl;
		if (!(cin>>numRows))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cerr<<"ERROR: could not read the number of rows in the input arrays:"<<endl;
			tries++;
			continue;
		}
		else if (numRows <= 0 || numRows > MAX_ARRAY_SIZE)
		{
			cerr<<"ERROR: the number of rows in the input arrays is out of range"<<endl;
			cout<<"Number of rows should be positive and <= "<<MAX_ARRAY_SIZE<<endl;
			tries++;
			continue;
		}
		else
		{
			breakFlag = true;
		}
	}

	if (tries > MAX_TRIES)
	{
		cerr<<"ERROR: too mnay tries: program terminating";
		return 0;
	}

	//prompt for number of columns
	breakFlag = false;
	while (breakFlag == false)
	{
		cout<<"Please enter the number of columns in the input arrays: "<<endl;
		if (!(cin>>numCols))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cerr<<"ERROR: could not read the number of columns in the input arrays:"<<endl;
			
			continue;
		}
		else if (numCols <= 0 || numCols > MAX_ARRAY_SIZE)
		{
			cerr<<"ERROR: the number of columns in the input arrays is out of range"<<endl;
			cout<<"length should be positive and <= "<<MAX_ARRAY_SIZE<<endl;
			
			continue;
		}
		else
		{
			breakFlag = true;
		}
	}

	//prompt for seed value
	breakFlag = false;
	while (breakFlag == false)
	{
		cout<<"Please enter the seed for the first input array: "<<endl;
		if (!(cin>>seed1))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cerr<<"ERROR: could not read the seed for the first input array:"<<endl;
			continue;
		}
		else if (seed1 <= 0 || seed1 > RAND_MAX)
		{
			cerr<<"ERROR: the seed for the first input arrays is invalid"<<endl;
			cout<<"seed should be non-negative and <= "<<RAND_MAX<<endl;
			continue;
		}
		else
		{
			breakFlag = true;
		}
	}

	//Generate seed2
	seed2 = (seed1 / 2) + 1;

	//Prompt for max Integer
	breakFlag = false;
	while (breakFlag == false)
	{
		cout<<"Please enter the largest random number to generate:"<<endl;
		if (!(cin>> maxInt))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cerr<<"ERROR: Could not read the largest random integer."<<endl;
			continue;
		}
		else if (maxInt <= MIN_RAND_INT || maxInt > MAX_RAND_INT)
		{
			cerr<<"ERROR: largest random integer is invalid"<<endl;
			cout<<"largest random integer should be non-negative, <  "<<MAX_RAND_INT<<endl;
			continue;
		}
		else
		{
			breakFlag = true;
		}
	}

	minInt = (maxInt/ 3) + 1;

	//Call Generate 2D to fill plotArray1
	Generate2D(plotArray1, numCols, numRows, seed1, minInt, maxInt);

	//Call Generate 2D to fill plotArray2
	Generate2D(plotArray2, numCols, numRows, seed2, minInt, maxInt);


	//Generate Pattern
	for (int a = 0; a < numRows; a++)
	{
		for (int h = 0; h < numCols; h++)
		{
			plotArray[a][h] = 0;
		}
	}

	for (int m = 0; m < numRows && m < numCols; m++)
	{
		plotArray[m][m] = 1;
	}

	//Call point plot to screen
	PointPlot(plotArray, numRows, numCols, cout);
	//Call point plot  to file
	PointPlot(plotArray, numRows, numCols, outFile);

	//Count Xs
	numOfX = countXs(plotArray, numRows, numCols);

	cout<<"Plotted array contains "<<numOfX<<" points";
	cout<<endl<<endl;
	outFile<<endl<<endl;

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			cout<<setw(3)<<(plotArray1[i][j] - plotArray2[i][j])<<" ";
		}
		cout<<endl;
	}
	cout<<endl;


	//Reset Plot Array
	for (int a = 0; a < MAX_ARRAY_SIZE; a++)
	{
		for (int  g = 0; g < MAX_ARRAY_SIZE; g++)
		{
			plotArray[a][g] = -1000;
		} 
	}


	//Place Values into plotArray
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			if ((plotArray1[i][j] - plotArray2[i][j]) < 0)
			{
				plotArray[i][j] = 1;
			}
		}
	}


	//Call point plot to screen
	PointPlot(plotArray, numRows, numCols, cout);
	//Call point plot  to file
	PointPlot(plotArray, numRows, numCols, outFile);

	//Count Xs
	numOfX = countXs(plotArray, numRows, numCols);

	cout<<"Plotted array contains "<<numOfX<<" points";
	cout<<endl<<endl;
	outFile<<endl<<endl;


	outFile.close();

return 0;
}


void Generate2D(int random2D[][MAX_ARRAY_SIZE], int numberCols, int numberRows, int seed, int minValue, int maxValue)
{
	//intialize random number generator
	srand(seed);

	int range = maxValue - minValue;

	for (int a = 0; a < numberRows; a++)
	{
		for (int f = 0; f < numberCols; f++)
		{
			random2D[a][f] = (rand() % range) + minValue;
		}
	}

}


void PointPlot(int scatterData[][MAX_ARRAY_SIZE], int rowLength, int columnLength, ostream& outstream)
{
	int counter = 0;

	for (int m = 0; m < rowLength; m++)
	{
		outstream<<"\t\t |";
		for (int k = 0; k < columnLength; k++)
		{
			if (scatterData[m][k] == 1)
			{
				outstream<<setw(2)<<"X";
			}
			else
			{
				outstream<<setw(2)<<" ";
			}
		}
		outstream<<endl;
	}

	outstream<<"\t\t";
	while(counter <= columnLength)
	{
		outstream<<" +";
		counter++;
	}

	outstream<<endl<<endl;
}


int countXs(int scatterData[][MAX_ARRAY_SIZE], int rowLength, int columnLength)
{
	int numXs = 0;

	for (int a = 0; a <rowLength; a++)
	{
		for (int f = 0; f < columnLength; f++)
		{
			if(scatterData[a][f] == 1)
			{
				numXs++;
			}
		}
	}

	return numXs;

}