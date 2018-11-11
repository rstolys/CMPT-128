#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

/*
*This program will take input values from a file that simulates the values coming from a coin counter.
*It will determine if the coins are valid, what type the coins are and sort them accordingly.
*The program will then print a summary of the sorting process

*Author: Ryan Stolys
*
*Complete: 05-11-17
*/

int main()
{
	//Declare file names
	char inName[1024] = {'0'};
	char outName[1024] = {'0'};
	ifstream inFile;
	ofstream outFile;

	//String constants
	const string bendGood = "usable";
	const string bendBad = "bent";
	const string matchGood = "BothMatch";
	const string matchBad1 = "OneMatch";
	const string matchBad2 = "NoMatch";

	//Declare varaibles 
	int weightIn;
	string weightInStr;
	int diameterIn;
	string diamterInStr;
	string bend = " ";
	string match = " ";
	double weightCalc = 0.0;
	double diameterCalc = 0.0;
	double weight = 0.0;
	double diameter = 0.0;

	int numLines = 0;
	string lineString;
	string voidVar = " ";
	string coinType = " ";
	string otherCoin = "Other";
	string testOutName = " ";
	string testInName = " ";

	int nickelRoll = 0;
	int dimeRoll = 0;
	int quarterRoll = 0;
	int loonieRoll = 0;
	int toonieRoll = 0;

	//Declare coin containers
	double bentContainer = 0.0;
	double otherContainer = 0.0;
	double bentContainerTotal = 0.0;
	double otherContainerTotal = 0.0;

	int otherContainerCount = 0;
	int otherCoinsTotal = 0;
	int otherCoins = 0;

	int nickelRollCount = 0;
	int dimeRollCount = 0;
	int quarterRollCount = 0;
	int loonieRollCount = 0;
	int toonieRollCount = 0;
	
	//Decalre Counters
	int triesIn = 0;
	int triesOut = 0;
	int numLinesCount = 1;
	bool breakFlag = false;

	//Declare constants 
	int const MAX_BENT_CONTAINER = 100;
	int const MAX_OTHER_CONTAINER = 200;
	int const MAX_TRIES_IN = 3;
	int const MAX_TRIES_OUT = 3;
	int const MIN_LINES = 1;
	int const MAX_LINES = 5000;
	int const MAX_WEIGHT_IN = 255;
	int const MIN_WEIGHT_IN = 0;
	int const MAX_DIAMETER_IN = 255;
	int const MIN_DIAMETER_IN = 0;

	double const MAX_NIC_WEIGHT = 4.3;
	double const MIN_NIC_WEIGHT = 3.6;
	double const MAX_DIM_WEIGHT = 2.2;
	double const MIN_DIM_WEIGHT = 1.3;
	double const MAX_QUART_WEIGHT = 4.8;
	double const MIN_QUART_WEIGHT = 4.0;
	double const MAX_LOON_WEIGHT = 7.5;
	double const MIN_LOON_WEIGHT = 6.5;
	double const MAX_TOON_WEIGHT = 7.85;
	double const MIN_TOON_WEIGHT = 6.75;

	double const MIN_NIC_DIAMETER = 20.2;
	double const MAX_NIC_DIAMETER = 21.8;
	double const MIN_DIM_DIAMETER = 17.3;
	double const MAX_DIM_DIAMETER = 18.7;
	double const MIN_QUART_DIAMETER = 22.8;
	double const MAX_QUART_DIAMETER = 24.6;
	double const MIN_LOON_DIAMETER = 25.0;
	double const MAX_LOON_DIAMETER = 27.0;
	double const MIN_TOON_DIAMETER = 26.9;
	double const MAX_TOON_DIAMETER = 29.1;

	int const NIC_MAX_ROLL = 40;
	int const DIM_MAX_ROLL = 50;
	int const QUART_MAX_ROLL = 40;
	int const LOON_MAX_ROLL = 25;
	int const TOON_MAX_ROLL = 25;
	

	//Declare Calculation Constants
	double const WEIGHT_CONST = 2.0;
	double const WEIGHT_CONST_2 = 5.0;
	double const DIAMETER_CONST = 30.0;
	double const DIAMETER_CONST_2 = 10.0;

	

	while (triesIn < MAX_TRIES_IN)
	{
		//Prompt user for input file
		cout<<"Type the name of the input file containing sensor readings: "<<endl;
		cin>>inName;

		//Open input file
		inFile.open(inName);		

		//Check if file is open
		if (inFile.fail())
		{
			cerr<<"ERROR: File "<<inName<<" could not be opened for input"<<endl;
			triesIn++;
			//If max tries is reached - terminate program
			if (triesIn >= MAX_TRIES_IN)
			{
				cerr<<"ERROR: You exceeded maximum number of tries allowed"<<endl<<"while entering the input file name";
				return 0;
			}
			inName [0] = 0;			//Reset array to read new values
			continue;
		}
		else
		{
			break;			//Exit loop if file is open
		}
	}
	
	
	while (triesOut < MAX_TRIES_OUT)
	{
		//Prompt user for output file
		cout<<"Type the name of the output file which will hold the simulation results:"<<endl;
		cin>>outName;

		//Set names of files to strings for comparison
		testOutName = outName;
		testInName = inName;

		//Test if file names are the same
		if (testOutName == testInName)
		{
			cerr<<"ERROR: File "<<outName<<" could not be opened for output"<<endl;
			outName[0] = 0;				//Reset array to read new values
			triesOut++;
			//If max tries is reached - terminate program
			if (triesOut >= MAX_TRIES_OUT)
			{
				cerr<<"ERROR: You exceeded maximum number of tries allowed"<<endl<<"while entering the output file name";
				return 0;
			}
			continue;
		}

		//Test if file exists
		outFile.open(outName);

		if (outFile.fail())		//If file doesn't exist
		{
			triesOut++;
			//If max tries is reached - terminate program
			if (triesOut >= MAX_TRIES_OUT)
			{
				cerr<<"ERROR: You exceeded maximum number of tries allowed"<<endl<<"while entering the output file name";
				return 0;
			}
			cerr<<"ERROR: File "<<outName<<" could not be opened for output"<<endl;
			outName[0] = 0;			//Reset array to read new values
			continue;
		}
		else
		{
			break;
		}
		
	}

		//Read number of lines in input file
		if (!(inFile>>numLines))		
		{
			//Check if file is empty
			if (inFile.eof())
			{
				cerr<<"ERROR: Input data file is empty";
				inFile.close();
				outFile.close();
				return 0;
			}
			//If file begins with non-integer value
			cerr<<"ERROR: First piece of data in the file is not an integer";
			inFile.close();
			outFile.close();
			return 0;
		}

		//Check to ensure value is within range
		if (numLines < MIN_LINES || numLines > MAX_LINES)
		{
			cerr<<"ERROR: The number of sensor readings is out of range";
			inFile.close();
			outFile.close();
			return 0;
		}


	/*	
		The following loop will read the file for the values
		Enusre the values gatherthered are legal and follow the formatting indicated
		Deal with lines and values which do not follow proper formatting
		Distribute the coins to the correct containers based on the information in the file
	*/

	while (numLinesCount < numLines)
	{
		//Reset Breakflag
		breakFlag = false;

		//Test for end of file -- Break loop is true
		if (inFile.eof())
		{
			cerr<<"ERROR: No more data"<<endl;
			cerr<<"Simulation completed early before line "<<numLinesCount<<" of input"<<endl;
			break;
		}

		//Collect one line from file
		getline (inFile, lineString);

		/*//Testing/ Debugging 
		cout<<endl<<endl<<endl<<lineString;*/

		//Turn line string into input stream for reading
		istringstream lineValues(lineString);

		/*//Testing/ Degbugging
		cout<<endl<<endl<<lineValues;*/

		//Read first value on line into string variable
		if (!(lineValues>>weightInStr))		//If false there is no information on the line (blank line)
		{
			continue;
		}

		//Turn weight string into input stream to read interger value
		istringstream value1(weightInStr);

		//Read value into varaible for first integer
		if (!(value1>>weightIn))		//If this is true, value is not an integer
		{
			cerr<<"ERROR: Weight sensor value read on line "<<numLinesCount<<" is not an integer"<<endl;
			cerr<<"Simulation terminated early: Please correct your data file";
			break;
		}

		//Test weight input for correct range
		if (weightIn < MIN_WEIGHT_IN || weightIn > MAX_WEIGHT_IN)
		{
			cerr<<"ERROR: Sensor reading out of range, ignoring line "<<numLinesCount<<" in the input file"<<endl;
			numLinesCount++;			//Increment number of lines read
			continue;
		}

		//Read second value on line
		if (!(lineValues>>diamterInStr))		//If true, only one value is on line
		{
			cerr<<"ERROR: Weight sensor measurement only"<<endl<<"Ignoring line "<<numLinesCount<<" of the input file"<<endl;
			numLinesCount++;			//Increment number of lines read
			continue;
		}

		//Make second value into input stream to read integer
		istringstream value2(diamterInStr);

		//Read value into integer varaible
		if (!(value2>>diameterIn))			//If this is true, value is not an integer
		{
			cerr<<"ERROR: Diameter sensor value read on line "<<numLinesCount<<" is not an integer"<<endl;
			cerr<<"Simulation terminated early: Please correct your data file";
			break;
		}

		//Test diameter input for correct range
		if (diameterIn < MIN_DIAMETER_IN || diameterIn > MAX_DIAMETER_IN)
		{
			cerr<<"ERROR: Sensor reading out of range, ignoring line "<<numLinesCount<<" in the input file"<<endl;
			numLinesCount++;			//Increment number of lines read
			continue;
		}

		//Read third value on line 
		if (!(lineValues>>bend))		//If true, no more values on line
		{
			cerr<<"ERROR: Weight and diameter sensor measurements only"<<endl;
			cerr<<"Ignoring line "<<numLinesCount<<" of the input file"<<endl;			
			numLinesCount++;			//Increment number of lines read
			continue;
		}

		//Test if input value matches input possibilities
		if (bend != bendGood && bend != bendBad)		//If true the value is not one of two possibilities
		{
			cerr<<"ERROR: Result of test to determine if coin is bent at line "<<numLinesCount<<" is invalid"<<endl;
			cerr<<"Ignoring this line of data"<<endl;
			numLinesCount++;			//Increment number of lines read
			continue;
		}

		//Read forth value on line
		if (!(lineValues>>match))		//If true, no values left on line
		{
			cerr<<"ERROR: Weight and diameter sensor measurements and bent string only"<<endl;
			cerr<<"Ignoring line "<<numLinesCount<<" of the input file"<<endl;			
			numLinesCount++;			//Increment number of lines read
			continue;
		}

		//Test if input value matches input possibilities
		if (match != matchBad1 && match != matchBad2 && match != matchGood)
		{
			cerr<<"ERROR: image processing result at line "<<numLinesCount<<" is invalid"<<endl;
			cerr<<"Ignoring this line of data"<<endl;	
			numLinesCount++;			//Increment number of lines read
			continue;
		}

		//Read for extra data on line
		if (lineValues>>voidVar)		//If true, extra data is on line
		{
			cerr<<"ERROR: Extra data at line "<<numLinesCount<<".  Ignoring extra data"<<endl;
		}

		/*	
			At this point the program has tested to ensure all the values are valid
			All the inputted values are within range and legal
			The program will now deal with the information
		*/

		//Change input values to doubles for calculations
		weightCalc = weightIn;
		diameterCalc = diameterIn;

		//Change the inputted values of weight and diameter into actaul values for measurements
		weight = (weightCalc/MAX_WEIGHT_IN)*WEIGHT_CONST*WEIGHT_CONST_2;

		diameter = (DIAMETER_CONST*(diameterCalc/MAX_DIAMETER_IN)) + DIAMETER_CONST_2;

		//Test if coin is bent - direct to appropriate container
		if (bend == bendBad)
		{
			bentContainerTotal += weight;		//Add coin weight to total bent weight
			if ((weight + bentContainer) < MAX_BENT_CONTAINER)
			{
				bentContainer += weight;		//Add coin weight to current bent weight
				//Print to screen
				cout<<"The Coin Sorter has sent this coin to the bent coin container"<<endl;
				cout<<"The coins in the bent coin container now weigh "<<fixed<<setw(6)<<setprecision(2)<<bentContainer<<" grams"<<endl;
				//Send to file
				outFile<<"The Coin Sorter has sent this coin to the bent coin container"<<endl;
				outFile<<"The coins in the bent coin container now weigh "<<fixed<<setw(6)<<setprecision(2)<<bentContainer<<" grams"<<endl;
				numLinesCount++;				//Increment line count
				continue;
			}
			else 
			{
				bentContainer = weight;			//Reset bent container and add new coin weight
				//Print to screen
				cout<<"The Coin Sorter has sent this coin to the bent coin container"<<endl;
				cout<<"This coin does not fit in the bent coin container"<<endl;
				cout<<"The bent coin container has been replaced"<<endl;
				cout<<"The coin in the new bent coin container weighs "<<fixed<<setw(6)<<setprecision(2)<<bentContainer<<" grams"<<endl;
				//Send to file
				outFile<<"The Coin Sorter has sent this coin to the bent coin container"<<endl;
				outFile<<"This coin does not fit in the bent coin container"<<endl;
				outFile<<"The bent coin container has been replaced"<<endl;
				outFile<<"The coin in the new bent coin container weighs "<<fixed<<setw(6)<<setprecision(2)<<bentContainer<<" grams"<<endl;
				numLinesCount++;				//Increment line count
				continue;
			}
		}

		//Reset coin type varaible
		coinType = "";

		//Test if coins image processing data is legal
		if (match != matchGood)
		{
			coinType = otherCoin;
		}

		//Test to see if weight matches canadian coin measurements and handle coin accordingly
		if (weight > MIN_NIC_WEIGHT && weight < MAX_NIC_WEIGHT && diameter > MIN_NIC_DIAMETER && diameter < MAX_NIC_DIAMETER && (coinType != otherCoin))
		{
				nickelRoll++;
				if (nickelRoll < NIC_MAX_ROLL)
				{
					//Print to screen
					cout<<"The Coin Sorter has sent one coin to the nickels wrapper"<<endl;
					cout<<"There are now "<<nickelRoll<<" coins in the nickels wrapper"<<endl;
					//Send to file
					outFile<<"The Coin Sorter has sent one coin to the nickels wrapper"<<endl;
					outFile<<"There are now "<<nickelRoll<<" coins in the nickels wrapper"<<endl;
					numLinesCount++;
					continue;
				}
				else
				{
					nickelRollCount++;			//Count total number of rolls
					nickelRoll = 0;
					//Print to screen
					cout<<"The Coin Sorter has sent one coin to the nickels wrapper"<<endl;
					cout<<"The nickel wrapper is now full"<<endl;
					cout<<"The nickel wrapper has now been replaced"<<endl;
					//Send to file
					outFile<<"The Coin Sorter has sent one coin to the nickels wrapper"<<endl;
					outFile<<"The nickel wrapper is now full"<<endl;
					outFile<<"The nickel wrapper has now been replaced"<<endl;
					numLinesCount++;
					continue;
				}
		}
		else if (weight > MIN_DIM_WEIGHT && weight < MAX_DIM_WEIGHT && diameter > MIN_DIM_DIAMETER && diameter < MAX_DIM_DIAMETER && (coinType != otherCoin))
		{
				dimeRoll++;
				if (dimeRoll < DIM_MAX_ROLL)
				{
					//Print to screen
					cout<<"The Coin Sorter has sent one coin to the dimes wrapper"<<endl;
					cout<<"There are now "<<dimeRoll<<" coins in the dimes wrapper"<<endl;
					//Send to file
					outFile<<"The Coin Sorter has sent one coin to the dimes wrapper"<<endl;
					outFile<<"There are now "<<dimeRoll<<" coins in the dimes wrapper"<<endl;
					numLinesCount++;
					continue;
				}
				else
				{
					dimeRollCount++;			//Count total number of rolls
					dimeRoll = 0;
					//Print to screen
					cout<<"The Coin Sorter has sent one coin to the dimes wrapper"<<endl;
					cout<<"The dime wrapper is now full"<<endl;
					cout<<"The dime wrapper has now been replaced"<<endl;
					//Send to file
					outFile<<"The Coin Sorter has sent one coin to the dimes wrapper"<<endl;
					outFile<<"The dime wrapper is now full"<<endl;
					outFile<<"The dime wrapper has now been replaced"<<endl;
					numLinesCount++;
					continue;
				}
		}
		else if (weight > MIN_QUART_WEIGHT && weight < MAX_QUART_WEIGHT && diameter > MIN_QUART_DIAMETER && diameter < MAX_QUART_DIAMETER && (coinType != otherCoin))
		{
				quarterRoll++;
				if (quarterRoll < QUART_MAX_ROLL)
				{
					//Print to screen
					cout<<"The Coin Sorter has sent one coin to the quarters wrapper"<<endl;
					cout<<"There are now "<<quarterRoll<<" coins in the quarters wrapper"<<endl;
					//Send to file
					outFile<<"The Coin Sorter has sent one coin to the quarters wrapper"<<endl;
					outFile<<"There are now "<<quarterRoll<<" coins in the quarters wrapper"<<endl;
					numLinesCount++;
					continue;
				}
				else
				{
					quarterRollCount++;			//Count total number of rolls
					quarterRoll = 0;
					//Print to Screen
					cout<<"The Coin Sorter has sent one coin to the quarters wrapper"<<endl;
					cout<<"The quarter wrapper is now full"<<endl;
					cout<<"The quarter wrapper has now been replaced"<<endl;
					//Send to file
					outFile<<"The Coin Sorter has sent one coin to the quarters wrapper"<<endl;
					outFile<<"The quarter wrapper is now full"<<endl;
					outFile<<"The quarter wrapper has now been replaced"<<endl;
					numLinesCount++;
					continue;
				}
		}
		else if (weight > MIN_LOON_WEIGHT && weight < MAX_LOON_WEIGHT && diameter > MIN_LOON_DIAMETER && diameter < MAX_LOON_DIAMETER && (coinType != otherCoin))
		{
				loonieRoll++;
				if (loonieRoll < LOON_MAX_ROLL)
				{
					//Print to screen
					cout<<"The Coin Sorter has sent one coin to the loonies wrapper"<<endl;
					cout<<"There are now "<<loonieRoll<<" coins in the loonies wrapper"<<endl;
					//Send to file
					outFile<<"The Coin Sorter has sent one coin to the loonies wrapper"<<endl;
					outFile<<"There are now "<<loonieRoll<<" coins in the loonies wrapper"<<endl;
					numLinesCount++;
					continue;
				}
				else
				{
					loonieRollCount++;			//Count total number of rolls
					loonieRoll = 0;
					//Print to Screen
					cout<<"The Coin Sorter has sent one coin to the loonies wrapper"<<endl;
					cout<<"The loonie wrapper is now full"<<endl;
					cout<<"The loonie wrapper has now been replaced"<<endl;
					//Send to file
					outFile<<"The Coin Sorter has sent one coin to the loonies wrapper"<<endl;
					outFile<<"The loonie wrapper is now full"<<endl;
					outFile<<"The loonie wrapper has now been replaced"<<endl;
					numLinesCount++;
					continue;
				}
		}
		else if (weight > MIN_TOON_WEIGHT && weight < MAX_TOON_WEIGHT && diameter > MIN_TOON_DIAMETER && diameter < MAX_TOON_DIAMETER && (coinType != otherCoin))
		{
				toonieRoll++;
				if (toonieRoll < TOON_MAX_ROLL)
				{
					//Print to screen
					cout<<"The Coin Sorter has sent one coin to the toonies wrapper"<<endl;
					cout<<"There are now "<<toonieRoll<<" coins in the toonies wrapper"<<endl;
					//Send to screen
					outFile<<"The Coin Sorter has sent one coin to the toonies wrapper"<<endl;
					outFile<<"There are now "<<toonieRoll<<" coins in the toonies wrapper"<<endl;
					numLinesCount++;
					continue;
				}
				else
				{
					toonieRollCount++;			//Count total number of rolls
					toonieRoll = 0;
					//Print to screen
					cout<<"The Coin Sorter has sent one coin to the toonies wrapper"<<endl;
					cout<<"The toonie wrapper is now full"<<endl;
					cout<<"The toonie wrapper has now been replaced"<<endl;
					//Send to file
					outFile<<"The Coin Sorter has sent one coin to the toonies wrapper"<<endl;
					outFile<<"The toonie wrapper is now full"<<endl;
					outFile<<"The toonie wrapper has now been replaced"<<endl;
					numLinesCount++;
					continue;
				}
		}
		else
		{
			coinType = otherCoin;
		}


		if (coinType == otherCoin)
		{
			otherContainerTotal += weight;		//Add weight to total other container weight
			otherCoinsTotal++;
			if ((otherContainer + weight) < MAX_OTHER_CONTAINER)
			{
				otherCoins++;
				otherContainer += weight;
				//Print to screen
				cout<<"The Coin Sorter has sent this coin to the other coin container"<<endl;
				cout<<"The coins in the other coin container now weigh "<<fixed<<setw(6)<<setprecision(2)<<otherContainer<<" grams"<<endl;
				//Send to file
				outFile<<"The Coin Sorter has sent this coin to the other coin container"<<endl;
				outFile<<"The coins in the other coin container now weigh "<<fixed<<setw(6)<<setprecision(2)<<otherContainer<<" grams"<<endl;
				numLinesCount++;
				continue;
			}
			else
			{
				otherContainerCount++;
				otherCoins = 1;
				otherContainer = weight;
				//Print to screen
				cout<<"The Coin Sorter has sent this coin to the other coin container"<<endl;
				cout<<"The coins in the other coin container now weigh "<<fixed<<setw(6)<<setprecision(2)<<otherContainer<<" grams"<<endl;
				//Send to file
				outFile<<"The Coin Sorter has sent this coin to the other coin container"<<endl;
				outFile<<"The coins in the other coin container now weigh "<<fixed<<setw(6)<<setprecision(2)<<otherContainer<<" grams"<<endl;
				numLinesCount++;
				continue;
			}
		}
		
		//Coin is now dealt with and loop will repeat for next coin so long as there is one. 

	}
	
	//Summary Results 

	//Print to screen
	cout<<endl<<endl<<endl<<"SUMMARY"<<endl;

	cout<<"The Coin Sorter made "<<setw(3)<<nickelRollCount<<" rolls of nickels."<<endl;
	cout<<"    There are "<<setw(2)<<nickelRoll<<" nickels in the partially full roll."<<endl;

	cout<<"The Coin Sorter made "<<setw(3)<<dimeRollCount<<" rolls of dimes."<<endl;
	cout<<"    There are "<<setw(2)<<dimeRoll<<" dimes in the partially full roll."<<endl;

	cout<<"The Coin Sorter made "<<setw(3)<<quarterRollCount<<" rolls of quarters."<<endl;
	cout<<"    There are "<<setw(2)<<quarterRoll<<" quarters in the partially full roll."<<endl;

	cout<<"The Coin Sorter made "<<setw(3)<<loonieRollCount<<" rolls of loonies."<<endl;
	cout<<"    There are "<<setw(2)<<loonieRoll<<" loonies in the partially full roll."<<endl;

	cout<<"The Coin Sorter made "<<setw(3)<<toonieRollCount<<" rolls of toonies."<<endl;
	cout<<"    There are "<<setw(2)<<toonieRoll<<" toonies in the partially full roll."<<endl;

	cout<<"The Coin Sorter processed "<<setw(5)<<otherCoinsTotal<<" other coins."<<endl;
	cout<<"    The other coins completely filled "<<setw(3)<<otherContainerCount<<" containers"<<endl;
	cout<<"    There were "<<setw(2)<<otherCoins<<" other coins in the partially full container"<<endl;
	cout<<"    The total weight of the other coins was "<<fixed<<setw(9)<<setprecision(3)<<otherContainerTotal<<" grams"<<endl;
	cout<<"The Coin Sorter processed "<<fixed<<setw(11)<<setprecision(4)<<bentContainerTotal<<" g of bent coins"<<endl;

	//Send to file
	outFile<<endl<<endl<<endl<<"SUMMARY"<<endl;

	outFile<<"The Coin Sorter made "<<setw(3)<<nickelRollCount<<" rolls of nickels."<<endl;
	outFile<<"    There are "<<setw(2)<<nickelRoll<<" nickels in the partially full roll."<<endl;

	outFile<<"The Coin Sorter made "<<setw(3)<<dimeRollCount<<" rolls of dimes."<<endl;
	outFile<<"    There are "<<setw(2)<<dimeRoll<<" dimes in the partially full roll."<<endl;

	outFile<<"The Coin Sorter made "<<setw(3)<<quarterRollCount<<" rolls of quarters."<<endl;
	outFile<<"    There are "<<setw(2)<<quarterRoll<<" quarters in the partially full roll."<<endl;

	outFile<<"The Coin Sorter made "<<setw(3)<<loonieRollCount<<" rolls of loonies."<<endl;
	outFile<<"    There are "<<setw(2)<<loonieRoll<<" loonies in the partially full roll."<<endl;

	outFile<<"The Coin Sorter made "<<setw(3)<<toonieRollCount<<" rolls of toonies."<<endl;
	outFile<<"    There are "<<setw(2)<<toonieRoll<<" toonies in the partially full roll."<<endl;

	outFile<<"The Coin Sorter processed "<<setw(5)<<otherCoinsTotal<<" other coins."<<endl;
	outFile<<"    The other coins completely filled "<<setw(3)<<otherContainerCount<<" containers"<<endl;
	outFile<<"    There were "<<setw(2)<<otherCoins<<" other coins in the partially full container"<<endl;
	outFile<<"    The total weight of the other coins was "<<fixed<<setw(9)<<setprecision(3)<<otherContainerTotal<<" grams"<<endl;
	outFile<<"The Coin Sorter processed "<<fixed<<setw(11)<<setprecision(4)<<bentContainerTotal<<" g of bent coins"<<endl;

	//Close files
	inFile.close();
	outFile.close();

	//Program is complete


	return 0;
}