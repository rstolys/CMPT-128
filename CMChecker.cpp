#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

/************************************************************************************************			
*This program will create the game called Cylindrical Mule Checkers.							*
*The program will create and print a game board, allow users to select locations of where		*
*their pieces will be moved and montior that all moves and rules are executed properly			*
*This program will allow the game to continue until one player wins.							*
*																								*
*Created by:	Ryan Stolys																		*
*				Jayden Cole																		*
*																								*
*Completed on: 20-11-27																			*
*************************************************************************************************/

//Define Global Constants
const int MAX_ARRAY_SIZE = 18;
const int MIN_ARRAY_SIZE = 8;
const int MAX_PIECES = 72;			
const int NOPLAYER = 0;				
const int WHITEWINS = 1;			
const int REDWINS = 2;
const int NOONEWINS = 0;
const int WHITESOLDIER = 1;
const int WHITEMULE = 2;
const int WHITEKING = 3;
const int REDSOLDIER = 4;
const int REDMULE = 5;
const int REDKING = 6;
const int WHITEPLAYER = 1;
const int REDPLAYER = 2;

//Function Prototypes
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
void DisplayBoard( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
int CountJumps( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[] );
bool CheckList( int inArray1[], int inArray2[], int xIndex, int yindex); 
int CountMove1Squares( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[],  int yLocArray[] );
bool IsMove1Squares( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc); 
bool IsJump( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);
bool MakeMove( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped );
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

//Custom Function Prototypes
void RowsInBoard(int &numRowsInBoard);
int setPlayerTurn(int turns);
void noMoreMoves(int playerTurn);
bool checkerSelect(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int &checkerSquare, int numRowsInBoard, int &yLoc, int &xLoc, int playerTurn);
void findOtherJumpers( int canJumpRecord[MAX_PIECES], int yIndicesJump[MAX_PIECES], int xIndicesJump[MAX_PIECES], int numRowsInBoard);
bool moveToSelect(int CMCheckerBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int &checkerMoveTo, int &yMoveLoc, int &xMoveLoc, int playerTurn);
bool shouldJump (int checkerSquare, int checkerMoveTo, int numRowsInBoard);
bool moveToSelectAgain(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int &checkerMoveTo, int &yMoveLoc, int &xMoveLoc, int playerTurn);
bool moveDownLeft (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc);
bool moveDownRight (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc);
bool moveUpLeft (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc);
bool moveUpRight (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc);
bool wrapAroundRightUp (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc, int numRows);
bool wrapAroundLeftUp (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc, int numRows);
bool wrapAroundRightDown (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc, int numRows);
bool wrapAroundLeftDown (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc, int numRows);
bool checkLocation (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int potentialX, int potentialY);
int checkerValueOnSquare (int CMCheckersBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int yLoc, int xLoc);

int main()
{
	//Declare Local Arrays
	int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
	int xIndicesMove[MAX_PIECES];
	int yIndicesMove[MAX_PIECES];
	int xIndicesJump[MAX_PIECES];
	int yIndicesJump[MAX_PIECES];
	int canJumpRecord[MAX_PIECES];


	//Declare Variables
	int numRowsInBoard = 0;
	int jumpOptions = 0;
	int moveOptions = 0;
	int playerTurn = 0;		
	int turns = 1;							//First turn will be turn 1
	char endGameChar;
	int checkerSquare = -1;					//Inialize to -1 to ensure selection will fail if entry fails
	int checkerMoveTo = -1;					//Inialize to -1 to ensure selection will fail if entry fails
	int yNowLoc = -1;						//Used to determine index of checkerSqaure and checkerMoveTo
	int xNowLoc = -1;
	int yMoveLoc = -1;
	int xMoveLoc = -1;
	bool didCheckerMove = false;
	bool canJump = false;
	bool canMove = false;
	
	bool moveMade = false;
	bool jumped = false;
	bool jumpAgain = false;
	bool winner = false;
	bool tempBoolean = false;
	bool switchFlag = false;

	//Declare counters
	int tries = 0;
	bool breakFlag = false;
	bool checkSelected = false;
	bool checkLocation = false;
	int index = 0;
	bool boardDisplayed = false;

	//Declare Strings
	string playerNow = " ";

	//Initalize my CMCheckersBoard Array
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (int g = 0; g < MAX_ARRAY_SIZE; g++)
		{
			myCMCheckersBoard[i][g] = 0;
		}
	}


	//Call Function to determine number of rows in board
	RowsInBoard(numRowsInBoard);
	//User input for rows in board is complete



	//Call function to initalize game board
	InitializeBoard(myCMCheckersBoard, numRowsInBoard);

	//Call function to print inital game board
	DisplayBoard(myCMCheckersBoard, numRowsInBoard);



	//Begin loop for each turn users will take
	while (winner == false)				//Winner is initalized to false
	{
		//Reset varaibles and arrays
		for (int i = 0; i < MAX_PIECES; i++)
		{
			canJumpRecord[i] = -1;				//Set all values of array to -1
		}
		canJump = false;						//Assume false unless tested to be true				
		canMove = false;						//Assume false unless tested to be true
		boardDisplayed = false;
		checkSelected = false;
		checkLocation = false;
		switchFlag = true;


		//Set player whose turn it is
		playerTurn = setPlayerTurn(turns);

		//Call functions to determine if any moves are possible
		moveOptions = CountMove1Squares(myCMCheckersBoard, numRowsInBoard, playerTurn, xIndicesMove, yIndicesMove);

		jumpOptions = CountJumps(myCMCheckersBoard, numRowsInBoard, playerTurn, xIndicesJump, yIndicesJump);

		//Check if player can move
		if ((moveOptions + jumpOptions) == 0)			
		{
			//Call noMoreMoves function to end game
			noMoreMoves(playerTurn);
		}
		
		//Promt player to execute turn

		//Set player turn and prompt user
		if (playerTurn == WHITEPLAYER)
		{
			playerNow = "White";
			cout<<playerNow<<" takes a turn"<<endl;
		}
		else
		{
			playerNow = "Red";
			cout<<playerNow<<" takes a turn"<<endl;
		}
		
		//Prompt for checker to move
		while (checkSelected == false)
		{
			//Assume input will be valid
			checkSelected = true;

			//Function will prompt user and check ERRORS  ***** cases 1 - 4 of entry ERRORS
			checkSelected = checkerSelect(myCMCheckersBoard, checkerSquare, numRowsInBoard, yNowLoc, xNowLoc, playerTurn);
			
			if (checkSelected == false)
			{
				continue;				//If error in input was found, restart loop
			}

			//Call CheckList Function to determine if piece can jump
			//The Location of the pieces is determined by the checkerSelect function
			//The Jump arrays are created by the IsJump function when it is called from the countJumps function
			canJump = CheckList(xIndicesJump, yIndicesJump, xNowLoc, yNowLoc);

			//If piece can't jump, Determine if other pieces can
			if (canJump == false)
			{
				//Call function to save locations of other  checkers that can jump
				findOtherJumpers(canJumpRecord, yIndicesJump, xIndicesJump, numRowsInBoard);

				if (canJumpRecord[0] != -1)			//If no piece can jump first value will be -1 and piece selected is legal
				{
					cerr<<"ERROR: You can jump with another checker, you may not move your chosen checker"<<endl;
					cout<<"You can jump using checkers on the following squares: ";
					for (index = 0; index < MAX_PIECES; index++)
					{
						if (canJumpRecord[index] != -1)
						{
							cout<<canJumpRecord[index]<<" ";		//Will print all values of legal jumping pieces
						}
						else
						{
							break;						//Once first value of -1 is reached, rest of array will be equal to -1
						}
					}
					cout<<endl<<"Try again"<<endl;
					checkSelected = false;
					continue;
				}
			}
			
			//Call CheckList function to determine if piece can move
			//The Location of the pieces is determined by the checkerSelect function
			//The Move arrays are created by the IsMove1Square function when it is called from the countMoves1Square function
			canMove = CheckList(xIndicesMove, yIndicesMove, xNowLoc, yNowLoc);
			if (canMove == false && canJump == false)			//If piece can jump, don't need to test of can move, piece must jump	
			{
				cerr<<"ERROR: There is no legal move for this checker"<<endl<<"Try again"<<endl;
				checkSelected = false;
				continue;
			}
		}
		//Checker to move has been successfully selected

		//Promt user to select location of checker to move to
		while (checkLocation == false)
		{
			//Assume input in correct
			checkLocation = true;

			//Function will prompt user and check some ERRORS  
			checkLocation = moveToSelect(myCMCheckersBoard, numRowsInBoard, checkerMoveTo, yMoveLoc, xMoveLoc, playerTurn);

			//check ERROR occured
			if (checkLocation == false)
			{
				continue;			//restart loop if error occured
			}

			//Check if checker is moved and if it is check if it should jump
			//Can jump value was set when checking input location of piece
			if (canJump == true)				//If the piece can jump
			{
				//Reset tempBoolean
				tempBoolean = false;
				//Call Function shouldJump
				tempBoolean = shouldJump (checkerSquare, checkerMoveTo, numRowsInBoard);
				
				if (tempBoolean == false)
				{
					checkLocation = false;
					continue;
				}
			}
			//Checker location to move to has been sucessfully selected

			//Call MakeMove Function to move checker to desired location
			moveMade = MakeMove(myCMCheckersBoard, numRowsInBoard, playerTurn, checkerSquare, checkerMoveTo, jumped);
			if (moveMade == false)
			{
				cerr<<"ERROR: moving to that square is not legal, Try again"<<endl;
				checkLocation = false;
				continue;					
			}		
		}		

		//Print Board if Move has been made
		if (moveMade == true)
		{
			DisplayBoard(myCMCheckersBoard, numRowsInBoard);		//Print board after successful move
		}

			
		while (jumped == true)				//If checker jumped, check if it can jump again
		{
			if (switchFlag == true)
			{
				//Set new loaction of Checker
				yNowLoc = yMoveLoc;
				xNowLoc = xMoveLoc;
				checkerSquare = checkerMoveTo;			//Set location of checker to new location 
				checkerMoveTo = -1;						//NULL move to location checker destination
			}
			//Call IsJump Function to determine if checker can jump again
			jumpAgain = IsJump(myCMCheckersBoard, numRowsInBoard, playerTurn, xNowLoc, yNowLoc);

			if (jumpAgain == true)			//If player can move again
			{
				checkLocation = false;					//Reset checkLocation to false to enter loop

				cout<<"You can jump again,  Please enter the next square you wish to move your checker to"<<endl;

				//Promt user to select location of check to move to
				while (checkLocation == false)
				{
					//Assume input in correct
					checkLocation = true;

					//Function will prompt user and check some ERRORS  
					checkLocation = moveToSelectAgain(myCMCheckersBoard, numRowsInBoard, checkerMoveTo, yMoveLoc, xMoveLoc, playerTurn);

					//check if an ERROR occured
					if (checkLocation == false)
					{
						continue;			//restart loop if error occured
					}

					//Check if checker that is supposed to jump is moved
					//This checker must jump

					//Reset tempBoolean
					tempBoolean = false;

					//Call Function shouldJump
					//This will test if future location is a move and will return error if is moved
					tempBoolean = shouldJump (checkerSquare, checkerMoveTo, numRowsInBoard);
				
					if (tempBoolean == false)
					{
						checkLocation = false;
						continue;
					}
				}			//End of loop for selecting location to move to
	

				//Reset moveMade boolean
				moveMade = false;
				//Call MakeMove function to move piece
				moveMade = MakeMove(myCMCheckersBoard, numRowsInBoard, playerTurn, checkerSquare, checkerMoveTo, jumped);

				if (moveMade == false)
				{
					cerr<<"ERROR: moving to that square is not legal, Try again"<<endl;
					switchFlag = false;
					continue;				//Restarts loop to jumpAgain Check
				}
				if (moveMade == true)
				{
					DisplayBoard(myCMCheckersBoard, numRowsInBoard);		//Print board after successful move
					switchFlag = true;
					continue;				//Move successfully made check if more jumps can be made
				}
			}
			else
			{
				jumped = false;		//If it can't jump again, set jumped to false and check for winner
			}
			
		}

		//Determine if CheckWin is true
		//If true, will set winner to true and loop will exit
		winner = CheckWin(myCMCheckersBoard, numRowsInBoard);

		turns++;		//Increment the turns counter
	}				//End of while loop for each turn

	//If one player wins game
	cout<<"Enter any character to terminate the game then press the enter key"<<endl;
	cin>>endGameChar;
	return 0;
}

//***********************************************
//Function Definitions of Required Functions	*
//***********************************************



//***********************************************************************
//Definition of InitializeBoard											*
//This function accepts the CheckersBoard pointer and initalizes it		*
//The function is called at the begging of the game to set the first 	*
//game board															*
//The function places specific numbers in their appropriate locations	*
//to indicate piece types of each player								*
//***********************************************************************
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	//Determine blank line rows
	int blank2 = numRowsInBoard/2;
	int blank1 = blank2 - 1;

	//Determine rows for Mules
	int whiteMuleRow = 0;
	int redMuleRow = numRowsInBoard - 1;

	//Determine first rows for soldiers
	int whiteSoldierRow = blank1 - 1;		//All rows between this and mules are soliders
	int redSoldierRow = blank2 + 1;			//All rows between this and mules are soliders



	for (int r = 0; r < numRowsInBoard; r++)
	{
		for (int c = 0; c < numRowsInBoard; c++)
		{
			//Set White mules
			if (r == whiteMuleRow && (c % 2) == 1)
			{
				CMCheckersBoard[r][c] = 2;
			}
			else if (r > whiteMuleRow && r <= whiteSoldierRow)		//Set White soldiers
			{
				if ((r % 2) == 1)					//If row is odd
				{
					if ((c % 2) == 0)				// And column is even
					{
						CMCheckersBoard[r][c] = 1;
					}
					else 
					{
						CMCheckersBoard[r][c] = 0;		//Fill other locations with zero
					}
				}
				else if ((r % 2) == 0)				//If row is even
				{
					if ((c % 2) == 1)				// And column is odd
					{
						CMCheckersBoard[r][c] = 1;
					}
					else 
					{
						CMCheckersBoard[r][c] = 0;		//Fill other locations with zero
					}
				}
			}
			else if (r == redMuleRow && (c % 2) == 0)		//Set Red mules
			{
				CMCheckersBoard[r][c] = 5;
			}
			else if (r < redMuleRow && r >= redSoldierRow)		//Set Red soldiers
			{
				if ((r % 2) == 0)					//If row is even
				{
					if ((c % 2) == 1)				// And column is odd
					{
						CMCheckersBoard[r][c] = 4;
					}
					else 
					{
						CMCheckersBoard[r][c] = 0;		//Fill other locations with zero
					}
				}
				else if ((r % 2) == 1)				//If row is odd
				{
					if ((c % 2) == 0)				// And column is even
					{
						CMCheckersBoard[r][c] = 4;
					}
					else 
					{
						CMCheckersBoard[r][c] = 0;		//Fill other locations with zero
					}
				}
			}
			else 
			{
				CMCheckersBoard[r][c] = 0;				//Set all other locations to zero
			}
		}
	}
}



//***********************************************************************
//Definition of DisplayBoard											*
//This function accepts the Checker Board pointer and prints it 		*
//The function will print certain numbers or abbreviations on the board	*
//to indicate to the players the location of each of their pieces		*
//***********************************************************************
void DisplayBoard( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int integerLocation = 0;

	for (int r = 0; r < numRowsInBoard; r++)
	{
		for (int c = 0; c < numRowsInBoard; c++)
		{
			if (CMCheckersBoard[r][c] == 1)		
			{
				cout<<setw(4)<<"WS";
			}
			else if (CMCheckersBoard[r][c] == 2)
			{
				cout<<setw(4)<<"WM";
			}
			else if (CMCheckersBoard[r][c] == 3)
			{
				cout<<setw(4)<<"WK";
			}
			else if (CMCheckersBoard[r][c] == 4)
			{
				cout<<setw(4)<<"RS";
			}
			else if (CMCheckersBoard[r][c] == 5)
			{
				cout<<setw(4)<<"RM";
			}
			else if (CMCheckersBoard[r][c] == 6)
			{
				cout<<setw(4)<<"RK";
			}
			else
			{
				cout<<setw(4)<<integerLocation;
			}

			//Increment location
			integerLocation++;
		}
		cout<<endl;
	}
}



//***********************************************************************
//Definition of CountJumps												*
//This function determines how many jumps the specified player can make	*
//The function will call on the IsJump function to check if each piece 	*
//can jump and then increment a counter to keep track of the total 		*
//number of possibilities while it saves the location of that checker to*
//the xLocArray and yLocArray											*
//The function will return an integer value indicating the number of	*
//jump possibilities for the indicated player							*
//***********************************************************************
int CountJumps( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[] )
{
	int numberJumps = 0;
	bool canJump = false;
	int xLocation = -1;
	int yLocation = -1;
	int index = 0;
	int pieceType = 0;

	//Initalize Arrays
	for (int a = 0; a < numRowsInBoard; a++)
	{
		xLocArray[a] = -1;				
		yLocArray[a] = -1;				
	}

	for (int rows = 0; rows < numRowsInBoard; rows++)
	{
		for (int columns = 0; columns < numRowsInBoard; columns++)			//For each element of the array
		{
			pieceType = CMCheckersBoard[rows][columns];						//Check type of piece
			if (player == WHITEPLAYER)
			{
				if (pieceType == WHITEKING || pieceType == WHITESOLDIER || pieceType == WHITEMULE)
				{
					canJump = false;
					canJump = IsJump(CMCheckersBoard, numRowsInBoard, player, columns, rows);		//Test if it can jump
					if (canJump == true)
					{
						numberJumps++;						//Record how many pieces can jump
						xLocArray[index] = columns;			//Record the location of the pieces that can jump
						yLocArray[index] = rows;
						index++;							//Increment the index of the piece location arrays
					}
				}
			}
			else if (player == REDPLAYER)
			{
				if (pieceType == REDKING || pieceType == REDSOLDIER || pieceType == REDMULE)
				{
					//Reset canJump 
					canJump = false;
					canJump = IsJump(CMCheckersBoard, numRowsInBoard, player, columns, rows);		//Test if it can jump
					if (canJump == true)
					{
						numberJumps++;						//Record how many pieces can jump
						xLocArray[index] = columns;			//Record the location of the pieces that can jump
						yLocArray[index] = rows;
						index++;							//Increment the index of the piece location arrays
					}
				}
			}
		}
	}
	
	return numberJumps;
}



//***********************************************************************
//Definition of CheckList												*
//The parameter xIndex and yIndex refer to a location on the board		*
//The function will check if that location matches the checkers saved 	*
//in the arrays inArray1 and inArray2									*
//The function will return a boolean result depending on the success of	*
//the check																*
//***********************************************************************
bool CheckList( int inArray1[], int inArray2[], int xIndex, int yindex)
{
	for (int i = 0; i < MAX_PIECES; i++)
	{
		if (yindex == inArray2[i])						//Test if row values match
		{
			for (int d = 0; d < MAX_PIECES; d++)		//Test if column values match
			{
				if (xIndex == inArray1[d])
				{
					return true;						//If both match, return true
				}
			}
		}
	}
	return false;										//If no match is found, return false
}



//***********************************************************************
//Definition of CountMove1Sqaures										*
//This function determines how many single square moves the specified	*
//player can make														*
//The function will call on the IsMove1Sqaure function to check if each *
//piece can move and then increment a counter to keep track of the total*
//number of possibilities while it saves the location of the moveable	*
//checkers and saves their location in the xLocArray and yLocArray		*
//The function will return an integer value indicating the number of	*
//1 quare move possibilities for the indicated player					*
//***********************************************************************
int CountMove1Squares( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[],  int yLocArray[] )
{
	int numberMoves = 0;
	bool canMove = false;
	int xLocation = -1;
	int yLocation = -1;
	int index = 0;
	int pieceType = 0;

	//Initalize Arrays
	for (int a = 0; a < numRowsInBoard; a++)
	{
		xLocArray[a] = -1;				
		yLocArray[a] = -1;				
	}

	for (int rows = 0; rows < numRowsInBoard; rows++)
	{
		for (int columns = 0; columns < numRowsInBoard; columns++)			//For each element of the array
		{
			pieceType = CMCheckersBoard[rows][columns];						//Check type of piece
			if (player == WHITEPLAYER)
			{
				if (pieceType == WHITEKING || pieceType == WHITESOLDIER || pieceType == WHITEMULE)
				{
					canMove = false;
					canMove = IsMove1Squares(CMCheckersBoard, numRowsInBoard, player, columns, rows);		//Test if it can jump
					if (canMove == true)
					{
						numberMoves++;						//Record how many pieces can jump
						xLocArray[index] = columns;			//Record the location of the pieces that can jump
						yLocArray[index] = rows;
						index++;							//Increment the index of the piece location arrays
					}
				}
			}
			else if (player == REDPLAYER)
			{
				if (pieceType == REDKING || pieceType == REDSOLDIER || pieceType == REDMULE)
				{
					//Reset canJump 
					canMove = false;
					canMove = IsMove1Squares(CMCheckersBoard, numRowsInBoard, player, columns, rows);		//Test if it can jump
					if (canMove == true)
					{
						numberMoves++;						//Record how many pieces can jump
						xLocArray[index] = columns;			//Record the location of the pieces that can jump
						yLocArray[index] = rows;
						index++;							//Increment the index of the piece location arrays
					}
				}
			}
		}
	}
	
	return numberMoves;
}



//***************************************************************************
//Definition of IsMove1Squares												*
//This function accepts information about a specific piece in question		*
//The function will check what type of piece it is and determine if it can	*
//move based on its limitations due to its type and other pieces that are	*
//in its way																*
//The function returns a boolean value depending on a pieces ability to move*
//***************************************************************************
bool IsMove1Squares( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	if (player == WHITEPLAYER)
	{
		//Check to see if the checker is on one of the end rows, and if so, which one
		if (xLoc == (numRowsInBoard - 1))
		{
			if (yLoc != (numRowsInBoard - 1)) //The checker is checked if it is in the bottom row
			{
				//Ckecker is on the right hand column of the board, below are the two functions that check the places where it can move
				if (moveDownLeft(CMCheckersBoard, xLoc, yLoc))
				{
					return true;
				}
				if (wrapAroundRightDown(CMCheckersBoard, xLoc, yLoc, numRowsInBoard))
				{
					return true;
				}
			}
		}

		else if (xLoc == 0)		//If checker is in the left hand column of the board, the two places where it can move are checked
		{
			if (yLoc != (numRowsInBoard - 1)) //The checker is checked if it is in the bottom row
			{
				if (moveDownRight(CMCheckersBoard, xLoc, yLoc))
				{
					return true;
				}
				if (wrapAroundLeftDown(CMCheckersBoard, xLoc, yLoc, numRowsInBoard))
				{
					return true;
				}
			}
		}
		else					//If Checker is in the middle of the board, both places where the checker can go are checked
		{
			if (yLoc != (numRowsInBoard - 1)) //The checker is checked if it is in the bottom row
			{
				if (moveDownLeft(CMCheckersBoard, xLoc, yLoc))
				{
					return true;
				}
				if (moveDownRight(CMCheckersBoard, xLoc, yLoc))
				{
					return true;
				}
			}
		}

		if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)		//if the piece is a king, check in the other direction as well
		{
			if (yLoc != 0)
			{
				if (moveUpLeft(CMCheckersBoard, xLoc, yLoc))
				{
					return true;
				}
				if (moveUpRight(CMCheckersBoard, xLoc, yLoc))
				{
					return true;
				}
			}
		}

		return false;
	}

	else //Player is Red
	{
		//Check to see if the checker is on one of the end rows, and if so, which one
		if (xLoc == (numRowsInBoard - 1))
		{
			if (yLoc != 0)
			{
				//Ckecker is on the right hand column of the board, below are the two functions that check the places where it can move
				if (moveUpLeft(CMCheckersBoard, xLoc, yLoc))
				{
					return true;
				}
				if (wrapAroundRightUp(CMCheckersBoard, xLoc, yLoc, numRowsInBoard))
				{
					return true;
				}
			}
		}

		else if (xLoc == 0)		//If checker is in the left hand column of the board
		{
			if (yLoc != 0)
			{
				if (moveUpRight(CMCheckersBoard, xLoc, yLoc))
				{
					return true;
				}
				if (wrapAroundLeftUp( CMCheckersBoard, xLoc, yLoc, numRowsInBoard))
				{
					return true;
				}
			}
		}

		else					//If Checker is in the middle of the board
		{
			if (yLoc != 0)
			{
				if (moveUpLeft(CMCheckersBoard, xLoc, yLoc))
				{
					return true;
				}
				if (moveUpRight(CMCheckersBoard, xLoc, yLoc))
				{
					return true;
				}
			}
		}

		if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)		//if the piece is a king, check in the other direction as well
		{
			if (yLoc != (numRowsInBoard - 1))
			{
				if (moveDownLeft(CMCheckersBoard, xLoc, yLoc))
				{
					return true;
				}
				if (moveDownRight(CMCheckersBoard, xLoc, yLoc))
				{
					return true;
				}
			}
		}

		return false;
	}
}




//*******************************************************************************
//Definition of IsJump															*
//This function accepts information about a specific piece in question			*
//The function will check what type of piece it is and determine if it can jump	*
//based on its limitations due to its type and other pieces	that are in its way	*
//or that are not close enough to jump											*
//The function returns a boolean value depending on the pieces ability to jump	*
//*******************************************************************************
bool IsJump( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
	{
	
	int jumpedSpaceValue = -1;
	int landingSpaceValue = -1;


	//Check whos turn it is
	if (player == REDPLAYER)
	{
		if (yLoc > 1)			//Jump up is possible as long as piece is not in top or second from top row
		{

			//*****************************************
			//Up and to the right                     *
			//*****************************************
			if (xLoc == (numRowsInBoard -2)) //Checker is on 2nd last column, will jump off the edge to the other side of the board
			{
				jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 1, xLoc + 1);
				landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc - 2, xLoc - (numRowsInBoard - 2));
			}
			else if (xLoc == (numRowsInBoard - 1)) //Checker is on last column, will jump off the edge to the other side of the board
			{
				jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 1, xLoc - (numRowsInBoard - 1));
				landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc - 2, xLoc - (numRowsInBoard - 2));
			}
			else 
			{
				jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 1, xLoc + 1);
				landingSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 2, xLoc + 2);
			}

			//If opponent is there, and there is a free space, isJump is true
			if (((jumpedSpaceValue == WHITESOLDIER ) || (jumpedSpaceValue == WHITEMULE) || (jumpedSpaceValue == WHITEKING)) && (landingSpaceValue == 0))
			{
				return true;
			}
		

			//*****************************************
			//Up and to the left                      *
			//*****************************************
			if (xLoc == 1) //Checker is on 2nd last column to the left, will jump off the edge to the other side of the board
			{
				jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 1, xLoc - 1);
				landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc - 2, xLoc + (numRowsInBoard - 2));
			}
			else if (xLoc == 0) //Checker is on last column to the left, will jump off the edge to the other side of the board
			{
				jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 1, xLoc + (numRowsInBoard - 1));
				landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc - 2, xLoc + (numRowsInBoard - 2));
			}
			else 
			{
				jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 1, xLoc - 1);
				landingSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 2, xLoc - 2);
			}

			//If opponent is there, and there is a free space, isJump is true
			if (((jumpedSpaceValue == WHITESOLDIER ) || (jumpedSpaceValue == WHITEMULE) || (jumpedSpaceValue == WHITEKING)) && (landingSpaceValue == 0))
			{
				return true;
			}
		}
		

		//****************************************************
		//Kings can move backward as well as forward,        *
		//check if the piece is a REDKING and if so, check   *
		//if it can jump backwards                           *
		//****************************************************

		if (CMCheckersBoard[yLoc][xLoc] == REDKING)
		{
			
			if (yLoc < numRowsInBoard - 2)		//King can jump down as long as it is not one of the bottom two rows
			{

				//*****************************************
				//Down and to the left                    *
				//*****************************************
				if (xLoc == 1) //Checker is on 2nd last column, will jump off the edge to the other side of the board
				{
					jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 1, xLoc - 1);
					landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc + 2, xLoc + (numRowsInBoard - 2));
				}
				else if (xLoc == 0) //Checker is on last column, will jump off the edge to the other side of the board
				{
					jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 1, xLoc + (numRowsInBoard - 1));
					landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc + 2, xLoc + (numRowsInBoard - 2));
				}
				else 
				{
					jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 1, xLoc - 1);
					landingSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 2, xLoc - 2);
				}


				//If opponent is there, and there is a free space, isJump is true
				if (((jumpedSpaceValue == WHITESOLDIER ) || (jumpedSpaceValue == WHITEMULE) || (jumpedSpaceValue == WHITEKING)) && (landingSpaceValue == 0))
				{
					return true;
				}
			
			
		
				//*****************************************
				//Down and to the right                   *
				//*****************************************

				if (xLoc == (numRowsInBoard -2)) //Checker is on 2nd last column, will jump off the edge to the other side of the board
				{
					jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 1, xLoc + 1);
					landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc + 2, xLoc - (numRowsInBoard - 2));
				}
				else if (xLoc == (numRowsInBoard - 1)) //Checker is on last column, will jump off the edge to the other side of the board
				{
					jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 1, xLoc - (numRowsInBoard - 1));
					landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc + 2, xLoc - (numRowsInBoard - 2));
				}
				else 
				{
					jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 1, xLoc + 1);
					landingSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 2, xLoc + 2);
				}

				//If opponent is there, and there is a free space, isJump is true
				if (((jumpedSpaceValue == WHITESOLDIER ) || (jumpedSpaceValue == WHITEMULE) || (jumpedSpaceValue == WHITEKING)) && (landingSpaceValue == 0))
				{
					return true;
				}
			}
		}
	}
	else //White player
	{

		if (yLoc < numRowsInBoard - 2)		//Piece can jump in down direction as long as it is not in one of the bottom two rows
		{
			//*****************************************
			//Down and to the left                    *
			//*****************************************
			if (xLoc == 1) //Checker is on 2nd last column, will jump off the edge to the other side of the board
			{
				jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 1, xLoc - 1);
				landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc + 2, xLoc + (numRowsInBoard - 2));
			}
			else if (xLoc == 0) //Checker is on last column, will jump off the edge to the other side of the board
			{
				jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 1, xLoc + (numRowsInBoard - 1));
				landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc + 2, xLoc + (numRowsInBoard - 2));
			}
			else 
			{
				jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 1, xLoc - 1);
				landingSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 2, xLoc - 2);
			}

			//If opponent is there, and there is a free space, isJump is true
			if (((jumpedSpaceValue == REDSOLDIER ) || (jumpedSpaceValue == REDMULE) || (jumpedSpaceValue == REDKING)) && (landingSpaceValue == 0))
			{
				return true;
			}

			//*****************************************
			//Down and to the right                   *
			//*****************************************

			if (xLoc == (numRowsInBoard -2)) //Checker is on 2nd last column, will jump off the edge to the other side of the board
			{
				jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 1, xLoc + 1);
				landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc + 2, xLoc - (numRowsInBoard - 2));
			}
			else if (xLoc == (numRowsInBoard - 1)) //Checker is on last column, will jump off the edge to the other side of the board
			{
				jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 1, xLoc - (numRowsInBoard - 1));
				landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc + 2, xLoc - (numRowsInBoard - 2));
			}
			else 
			{
				jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 1, xLoc + 1);
				landingSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc + 2, xLoc + 2);
			}

			//If opponent is there, and there is a free space, isJump is true
			if (((jumpedSpaceValue == REDSOLDIER ) || (jumpedSpaceValue == REDMULE) || (jumpedSpaceValue == REDKING)) && (landingSpaceValue == 0))
			{
				return true;
			}
		}
		

		//****************************************************
		//Kings can move backward as well as forward,        *
		//check if the piece is a WHITEKING and if so, check   *
		//if it can jump backwards                           *
		//****************************************************

		if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
		{

			if (yLoc > 1)			//King can jump up as long as it is not in one of top two rows
			{
				//*****************************************
				//Up and to the right                     *
				//*****************************************

				if (xLoc == (numRowsInBoard -2)) //Checker is on 2nd last column to the right, will jump off the edge to the other side of the board
				{
					jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 1, xLoc + 1);
					landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc - 2, xLoc - (numRowsInBoard - 2));
				}
				else if (xLoc == (numRowsInBoard - 1)) //Checker is on last column to the right, will jump off the edge to the other side of the board
				{
					jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 1, xLoc - (numRowsInBoard - 1));
					landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc - 2, xLoc - (numRowsInBoard - 2));
				}
				else 
				{
					jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 1, xLoc + 1);
					landingSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 2, xLoc + 2);
				}

				//If opponent is there, and there is a free space, isJump is true
				if (((jumpedSpaceValue == REDSOLDIER ) || (jumpedSpaceValue == REDMULE) || (jumpedSpaceValue == REDKING)) && (landingSpaceValue == 0))
				{
					return true;
				}

				//*****************************************
				//Up and to the left                      *
				//*****************************************

				if (xLoc == 1) //Checker is on 2nd last column to the left, will jump off the edge to the other side of the board
				{
					jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 1, xLoc - 1);
					landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc - 2, xLoc + (numRowsInBoard - 2));
				}
				else if (xLoc == 0) //Checker is on last column to the left, will jump off the edge to the other side of the board
				{
					jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 1, xLoc + (numRowsInBoard - 1));
					landingSpaceValue = checkerValueOnSquare (CMCheckersBoard, yLoc - 2, xLoc + (numRowsInBoard - 2));
				}
				else 
				{
					jumpedSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 1, xLoc - 1);
					landingSpaceValue = checkerValueOnSquare(CMCheckersBoard, yLoc - 2, xLoc - 2);
				}

				//If opponent is there, and there is a free space, isJump is true
				if (((jumpedSpaceValue == REDSOLDIER ) || (jumpedSpaceValue == REDMULE) || (jumpedSpaceValue == REDKING)) && (landingSpaceValue == 0))
				{
					return true;
				}
			}
		}
	}

	return false;	//If the piece in question cannot jump
}



//***************************************************************************
//Definition of MakeMove													*
//This function is responsible for moving the checker from its original		*
//location to the new indictaed location 									*
//This function will move the checker and also ensure the move made is		*
//legal based on the rules of movement and limitations of certain pieces	*
//The function returns a boolean value depending on the success of the move	*
//***************************************************************************
bool MakeMove( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped )
{
	char endGameChar = ' ';
	int jumpedPiece = 0;
	int pieceType = 0;
	bool moved = false;
	bool interiorMove = false;
	bool acrossMove = false;
	int xDistance = 0;
	int yDistance = 0;
	int xLocNow = fromSquareNum % numRowsInBoard;
	int xLocMove = toSquareNum % numRowsInBoard;
	int yLocNow = fromSquareNum / numRowsInBoard;
	int yLocMove = toSquareNum / numRowsInBoard;
	
	//Set values of x and y Distance
	xDistance = abs(xLocMove - xLocNow);
	yDistance = abs(yLocMove - yLocNow);

	//Collect piece type 
	pieceType = CMCheckersBoard[yLocNow][xLocNow];

	//Determine what situation it is
	if (yDistance > 0 && yDistance <= 2 && xDistance > 0 && xDistance <= 2)
	{
		//Move is within normal board square
		interiorMove = true;
	}
	else if (yDistance == 0 || xDistance == 0)
	{
		//Ilegal distance to move
		cerr<<"Error; illegal move"<<endl;
		return false;
	}
	else
	{
		//Move crosses over cylinder divider
		acrossMove = true;
	}

	//Interior Movement Case
	if (interiorMove == true)
	{
		if (player == WHITEPLAYER)
		{
			if (yDistance == 1 && xDistance == 1)
			{
				//Test piece Type
				if (pieceType == WHITEMULE || pieceType == WHITESOLDIER)
				{
					if ((yLocNow - yLocMove) != -1)				//White Mule and Solder must move in Down direction
					{
						cerr<<"Error; illegal move"<<endl;
						return false;
					}
					else
					{
						//If piece did move down then left or right move is legal
						moved = true;
					}
				}
				else if (pieceType == WHITEKING)
				{
					//King can move in any direction and left or right, move is legal
					moved = true;
				}
			}
			else if (yDistance == 2 && xDistance == 2)
			{
				//Piece type will determine legal movemnts
				if (pieceType == WHITEMULE || pieceType == WHITESOLDIER)
				{
					if (yLocMove == (yLocNow + 2) && xLocMove == (xLocNow + 2))			//Test Down Right Move
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow + 1];
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow + 1] = 0;			//Remove Piece
							jumped = true;											//Set jumped to true
							moved = true;											//Set moved to true
						}
					}
					else if (yLocMove == (yLocNow + 2) && xLocMove == (xLocNow - 2))	//Test Down Left Move
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow - 1];
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow - 1] = 0;			//Remove Piece
							jumped = true;											//Set jumped to true
							moved = true;											//Set moved to true
						}
					}
					else
					{
						//If move if not one of legal move options, move is illegal
						cerr<<"Error; illegal move"<<endl;
						return false;
					}
				}
				else if (pieceType == WHITEKING)
				{
					if (yLocMove == (yLocNow + 2) && xLocMove == (xLocNow + 2))			//Test Down Right Move
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow + 1];
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow + 1] = 0;			//Remove Piece
							jumped = true;											//Set jumped to true
							moved = true;											//Set moved to true
						}
					}
					else if (yLocMove == (yLocNow + 2) && xLocMove == (xLocNow - 2))	//Test Down Left Move
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow - 1];
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow - 1] = 0;			//Remove Piece
							jumped = true;											//Set jumped to true
							moved = true;											//Set moved to true
						}
					}
					else if (yLocMove == (yLocNow - 2) && xLocMove == (xLocNow + 2))	//Test Up Right Move
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow + 1];
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow + 1] = 0;			//Remove Piece
							jumped = true;											//Set jumped to true
							moved = true;											//Set moved to true
						}
					}
					else if (yLocMove == (yLocNow - 2) && xLocMove == (xLocNow -2))	//Test Up Left Move
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow - 1];
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow - 1] = 0;			//Remove Piece
							jumped = true;											//Set jumped to true
							moved = true;											//Set moved to true
						}
					}
					else
					{
						//If move if not one of legal move options, move is illegal
						cerr<<"Error; illegal move"<<endl;
						return false;
					}
				}
			}
		}
		else if (player == REDPLAYER)
		{
			if (yDistance == 1 && xDistance == 1)
			{
				if (pieceType == REDMULE || pieceType == REDSOLDIER)
				{
						if ((yLocNow - yLocMove) != 1)				//Red Mule and Solder must move in Up direction
					{
						cerr<<"Error; illegal move"<<endl;
						return false;
					}
					else
					{
						//If piece did move up then left or right move is legal
						moved = true;
					}
				}
				else if (pieceType == REDKING)
				{
					//King can move in any direction and left or right, move is legal
					moved = true;
				}
			}
			else if (yDistance == 2 && xDistance == 2)
			{
				//Piece type will determine legal movemnts
				if (pieceType == REDMULE || pieceType == REDSOLDIER)
				{
					if (yLocMove == (yLocNow - 2) && xLocMove == (xLocNow + 2))			//Test Up Right Move
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow + 1];
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow + 1] = 0;			//Remove Piece
							jumped = true;											//Set jumped to true
							moved = true;											//Set moved to true
						}
					}
					else if (yLocMove == (yLocNow - 2) && xLocMove == (xLocNow - 2))	//Test Up Left Move
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow - 1];
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow - 1] = 0;			//Remove Piece
							jumped = true;											//Set jumped to true
							moved = true;											//Set moved to true
						}
					}
					else
					{
						//If move if not one of legal move options, move is illegal
						cerr<<"Error; illegal move"<<endl;
						return false;
					}
				}
				else if (pieceType == REDKING)
				{
					if (yLocMove == (yLocNow + 2) && xLocMove == (xLocNow + 2))			//Test Down Right Move
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow + 1];
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow + 1] = 0;			//Remove Piece
							jumped = true;											//Set jumped to true
							moved = true;											//Set moved to true
						}
					}
					else if (yLocMove == (yLocNow + 2) && xLocMove == (xLocNow - 2))	//Test Down Left Move
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow - 1];
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow - 1] = 0;			//Remove Piece
							jumped = true;											//Set jumped to true
							moved = true;											//Set moved to true
						}
					}
					else if (yLocMove == (yLocNow - 2) && xLocMove == (xLocNow + 2))	//Test Up Right Move
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow + 1];
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow + 1] = 0;			//Remove Piece
							jumped = true;											//Set jumped to true
							moved = true;											//Set moved to true
						}
					}
					else if (yLocMove == (yLocNow - 2) && xLocMove == (xLocNow -2))	//Test Up Left Move
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow - 1];
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow - 1] = 0;			//Remove Piece
							jumped = true;											//Set jumped to true
							moved = true;											//Set moved to true
						}
					}
					else
					{
						//If move if not one of legal move options, move is illegal
						cerr<<"Error; illegal move"<<endl;
						return false;
					}
				}
			}
		}
	}	//End of interior Move 
	
	//Across the board case
	else if (acrossMove == true)			
	{
		if (player == WHITEPLAYER)
		{
			if (pieceType == WHITEMULE || pieceType == WHITESOLDIER)
			{
				if (yLocMove == (yLocNow + 1) && xLocMove == (xLocNow - (numRowsInBoard - 1)))			//Test Down and Right Move
				{
					moved = true;			//Move is legal
				}
				else if (yLocMove == (yLocNow + 1) && xLocMove == (xLocNow + (numRowsInBoard - 1)))		//Test Down and Left Move
				{
					moved = true;			//Move is legal
				}
				else if (yLocMove == (yLocNow + 2) && xLocMove == xLocNow - (numRowsInBoard - 2))		//Test Down and Right Jump
				{
					if (xLocNow == numRowsInBoard - 2)			//If Piece is in second last column, else it is in last column
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow + 1] ;
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow + 1] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
					else
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow - (numRowsInBoard - 1)] ;
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow - (numRowsInBoard - 1)] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
				}
				else if (yLocMove == (yLocNow + 2) && xLocMove == xLocNow + (numRowsInBoard - 2))		//Test Down and Left Jump
				{
					if (xLocNow == 1)			//If Piece is in second column, else it is in first column
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow - 1] ;
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow - 1] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
					else
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow + (numRowsInBoard - 1)] ;
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow + (numRowsInBoard - 1)] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
				}
				else 
				{
					//None of above moves match
					cerr<<"Error; illegal move"<<endl;
					return false;
				}
			}
			else if (pieceType == WHITEKING)
			{
				if (yLocMove == (yLocNow + 1) && xLocMove == (xLocNow - (numRowsInBoard - 1)))			//Test Down and Right Move
				{
					moved = true;			//Move is legal
				}
				else if (yLocMove == (yLocNow + 1) && xLocMove == (xLocNow + (numRowsInBoard - 1)))		//Test Down and Left Move
				{
					moved = true;			//Move is legal
				}
				else if (yLocMove == (yLocNow - 1) && xLocMove == xLocNow - (numRowsInBoard - 1))	//Test Up and Right Move
				{
					moved = true;			//Move is legal
				}
				else if (yLocMove == (yLocNow - 1) && xLocMove == xLocNow + (numRowsInBoard - 1))	//Test Up and Left Move
				{
					moved = true;			//Move is legal
				}
				else if (yLocMove == (yLocNow + 2) && xLocMove == xLocNow - (numRowsInBoard - 2))		//Test Down and Right Jump
				{
					if (xLocNow == numRowsInBoard - 2)			//If Piece is in second last column, else it is in last column
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow + 1] ;
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow + 1] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
					else
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow - (numRowsInBoard - 1)] ;
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow - (numRowsInBoard - 1)] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
				}
				else if (yLocMove == (yLocNow + 2) && xLocMove == xLocNow + (numRowsInBoard - 2))		//Test Down and Left Jump
				{
					if (xLocNow == 1)			//If Piece is in second column, else it is in first column
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow - 1] ;
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow - 1] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
					else
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow + (numRowsInBoard - 1)] ;
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow + (numRowsInBoard - 1)] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
				}
				else if (yLocMove == (yLocNow - 2) && xLocMove == xLocNow + (numRowsInBoard - 2))	//Test Up Left Jump
				{
					if (xLocNow == 1)			//If Piece is in second column, else it is in first column
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow - 1] ;
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow - 1] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
					else
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow + (numRowsInBoard - 1)] ;
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow + (numRowsInBoard - 1)] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
				}
				else if (yLocMove == (yLocNow - 2) && xLocMove == xLocNow - (numRowsInBoard - 2))	//Test Up Right Jump
				{
					if (xLocNow == numRowsInBoard - 2)			//If Piece is in second last column, else it is in last column
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow + 1] ;
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow + 1] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
					else
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow - (numRowsInBoard - 1)] ;
						if (jumpedPiece == REDMULE || jumpedPiece == REDSOLDIER || jumpedPiece == REDKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow - (numRowsInBoard - 1)] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
				}
				else 
				{
					//None of above moves match
					cerr<<"Error; illegal move"<<endl;
					return false;
				}
			}
		}	//End of white player Possibilities
		else if (player == REDPLAYER)
		{
			if (pieceType == REDMULE || pieceType == REDSOLDIER)
			{
				if (yLocMove == (yLocNow - 1) && xLocMove == xLocNow - (numRowsInBoard - 1))			//Test Up and Right Move
				{
					moved = true;			//Move is legal
				}
				else if (yLocMove == (yLocNow - 1) && xLocMove == xLocNow + (numRowsInBoard - 1))		//Test Up and Left Move
				{
					moved = true;			//Move is legal
				}
				else if (yLocMove == (yLocNow - 2) && xLocMove == xLocNow + (numRowsInBoard - 2))	//Test Up Left Jump
				{
					if (xLocNow == 1)			//If Piece is in second column, else it is in first column
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow - 1] ;
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow - 1] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
					else
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow + (numRowsInBoard - 1)] ;
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow + (numRowsInBoard - 1)] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
				}
				else if (yLocMove == (yLocNow - 2) && xLocMove == xLocNow - (numRowsInBoard - 2))	//Test Up Right Jump
				{
					if (xLocNow == numRowsInBoard - 2)			//If Piece is in second last column, else it is in last column
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow + 1] ;
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow + 1] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
					else
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow - (numRowsInBoard - 1)] ;
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow - (numRowsInBoard - 1)] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
				}
				else 
				{
					//None of above moves match
					cerr<<"Error; illegal move"<<endl;
					return false;
				}
			}
			else if (pieceType == REDKING)
			{
				if (yLocMove == (yLocNow + 1) && xLocMove == (xLocNow - (numRowsInBoard - 1)))			//Test Down and Right Move
				{
					moved = true;			//Move is legal
				}
				else if (yLocMove == (yLocNow + 1) && xLocMove == (xLocNow + (numRowsInBoard - 1)))		//Test Down and Left Move
				{
					moved = true;			//Move is legal
				}
				else if (yLocMove == (yLocNow - 1) && xLocMove == xLocNow - (numRowsInBoard - 1))		//Test Up and Right Move
				{
					moved = true;			//Move is legal
				}
				else if (yLocMove == (yLocNow - 1) && xLocMove == xLocNow + (numRowsInBoard - 1))		//Test Up and Left Move
				{
					moved = true;			//Move is legal
				}
					else if (yLocMove == (yLocNow + 2) && xLocMove == xLocNow - (numRowsInBoard - 2))		//Test Down and Right Jump
				{
					if (xLocNow == numRowsInBoard - 2)			//If Piece is in second last column, else it is in last column
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow + 1] ;
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow + 1] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
					else
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow - (numRowsInBoard - 1)] ;
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow - (numRowsInBoard - 1)] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
				}
				else if (yLocMove == (yLocNow + 2) && xLocMove == xLocNow + (numRowsInBoard - 2))		//Test Down and Left Jump
				{
					if (xLocNow == 1)			//If Piece is in second column, else it is in first column
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow - 1] ;
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow - 1] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
					else
					{
						jumpedPiece = CMCheckersBoard[yLocNow + 1][xLocNow + (numRowsInBoard - 1)] ;
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow + 1][xLocNow + (numRowsInBoard - 1)] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
				}
				else if (yLocMove == (yLocNow - 2) && xLocMove == xLocNow + (numRowsInBoard - 2))	//Test Up Left Jump
				{
					if (xLocNow == 1)			//If Piece is in second column, else it is in first column
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow - 1] ;
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow - 1] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
					else
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow + (numRowsInBoard - 1)] ;
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow + (numRowsInBoard - 1)] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
				}
				else if (yLocMove == (yLocNow - 2) && xLocMove == xLocNow - (numRowsInBoard - 2))	//Test Up Right Jump
				{
					if (xLocNow == numRowsInBoard - 2)			//If Piece is in second last column, else it is in last column
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow + 1] ;
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow + 1] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
					else
					{
						jumpedPiece = CMCheckersBoard[yLocNow - 1][xLocNow - (numRowsInBoard - 1)] ;
						if (jumpedPiece == WHITEMULE || jumpedPiece == WHITESOLDIER || jumpedPiece == WHITEKING)
						{
							CMCheckersBoard[yLocNow - 1][xLocNow - (numRowsInBoard - 1)] = 0;			//Remove Jumped Piece
							jumped = true;
							moved = true;
						}
					}
				}
				else 
				{
					//None of above moves match
					cerr<<"Error; illegal move"<<endl;
					return false;
				}
			}
		}
	}		//End of across board move

	//If moved is true, move piece and test if it is at end of board location
	if (moved == true)
	{
		//Move piece to new location
		CMCheckersBoard[yLocMove][xLocMove] = CMCheckersBoard[yLocNow][xLocNow];
		//Empty location which piece was moved from
		CMCheckersBoard[yLocNow][xLocNow] = 0;

		//Test if piece is at end of board for each player
		if (player == WHITEPLAYER && yLocMove == (numRowsInBoard - 1))		//If white player piece is at bottom of board
		{
			//Change piece to a king
			CMCheckersBoard[yLocMove][xLocMove] = WHITEKING;

			//Check to see if piece was a mule before 
			if (pieceType == WHITEMULE)
			{
				//Mule turned to king means game is over
				cout<<"White has created a Mule King, Red wins the game"<<endl;
				cout<<"Enter any chacter to terminate the game then press the enter key";
				cin>> endGameChar;
				exit (0);
			}
			else 
			{
				return true;				//Move was successful
			}
		}
		else if (player == REDPLAYER && yLocMove == 0)						//If red player piece is at top of board
		{
			//Change piece to king
			CMCheckersBoard[yLocMove][xLocMove] = REDKING;

			//Check to see if piece was a mule before 
			if (pieceType == REDMULE)
			{
				//Mule turned to king means game is over
				cout<<"Red has created a Mule King, White wins the game"<<endl;
				cout<<"Enter any chacter to terminate the game then press the enter key";
				cin>> endGameChar;
				exit (0);
			}
			else 
			{
				return true;				//Move was successful
			}
		}
		else
		{
			return true;
		}
	}

	
	//If function reaches this point, there has been an error
	return false;
	//End of Make Move Function
}



//*******************************************************************************
//Definition of CheckWin														*
//This function determines if one of the players has won the game				*
//The function checks a set of conditions that would result in the game ending	*
//The function will return a boolean value depending on the outcome of the		*
//conditions tested																*
//*******************************************************************************
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int redMuleCount = 0;
	int whiteMuleCount = 0;
	int redSoldKingCount = 0;
	int whiteSoldKingCount = 0;
	int pieceType = -1;

	for (int r = 0; r < numRowsInBoard; r++)
	{
		for (int c = 0; c < numRowsInBoard; c++)
		{
			pieceType = CMCheckersBoard[r][c];
			if (pieceType == REDMULE)
			{
				redMuleCount++;					//If piece is a Red Mule, increment counter
			}
			else if (pieceType == WHITEMULE)
			{
				whiteMuleCount++;				//If piece is a White Mule, increment counter
			}
			else if (pieceType == REDKING || pieceType == REDSOLDIER)
			{
				redSoldKingCount++;				//If piece is a Red Soldier or King
			}
			else if (pieceType == WHITEKING || pieceType == WHITESOLDIER)
			{
				whiteSoldKingCount++;			//If piece is a White Soldier or King
			}
		}
	}

	if (redMuleCount == 0)						//If there are no more Red Mules
	{
		cout<<"The Red Player has won the game by losing all of the Red Mules"<<endl;
		return true;
	}
	else if (whiteMuleCount == 0)				//If there are no more White Mules
	{
		cout<<"The White Player has won the game by losing all of the White Mules"<<endl;
		return true;
	}
	else if (redSoldKingCount == 0)				//If all Red Soldiers and Kings are gone
	{
		cout<<"The White Player has won by capturing all of the red players soldiers and kings"<<endl;
		return true;
	}
	else if (whiteSoldKingCount == 0)			//If all White Soldiers and Kings are gone
	{
		cout<<"The Red Player has won by capturing all of the white players soldiers and kings"<<endl;
		return true;
	}
	else
	{
		return false;							//If none of the above conditions are true, no player one, return false
	}
}






//*******************************************
//Function Definitions of Custom Functions	*
//*******************************************


//***********************************************************************
//Definition of RowsInBoard												*
//The parameter numRowsInBoard is a reference varaible					*
//The function will prompt the user for an input for the number of rows	*
//The function will then validate the user input type and range			*
//The function will keep count of the number of attempts to enter the	*
//number of rows and terminate the program if the attempts exceed 3		*
//***********************************************************************
void RowsInBoard(int &numRowsInBoard)
{
	//Declare Variables
	int tries = 0;
	int const MAX_TRIES = 3;
	bool breakFlag = false;

	//Declare constants
	int const MAX_BOARD_SIZE = 18;
	int const MIN_BOARD_SIZE = 8;

	//Prompt User for number of rows in board
	while (tries < MAX_TRIES && breakFlag == false)
	{
		cout<<"Enter the number of squares along each edge of the board"<<endl;			//Prompt user
		if (!(cin>>numRowsInBoard))			//Test if entry is integer
		{
			cin.clear();					//Clear Flag
			cin.ignore(10000, '\n');		//Clear buffer for 10000 charters or \n
			cerr<<"ERROR:  Board size is not an integer"<<endl;
			cout<<"8 <= number of squares <= 18"<<endl;
			tries++;
			continue;
		}
		else if ((numRowsInBoard % 2) == 1)		//Check if value entered is odd
		{
			cerr<<"ERROR:  Board size odd"<<endl;
			cout<<"8 <= number of squares <= 18"<<endl;
			tries++;
			continue;
		}
		else if (numRowsInBoard < MIN_BOARD_SIZE)				//Check if value is too small
		{
			cerr<<"ERROR:  Board size too small"<<endl;
			cout<<"8 <= number of squares <= 18"<<endl;
			tries++;
			continue;
		}
		else if (numRowsInBoard > MAX_BOARD_SIZE)			//Check if value is too large
		{
			cerr<<"ERROR:  Board size too large"<<endl;
			cout<<"8 <= number of squares <= 18"<<endl;
			tries++;
			continue;
		}
		else
		{
			breakFlag = true;				//Set break flag to true to exit loop
		}
	}

	if (tries >= MAX_TRIES)					//If max tries reached, exit program
	{
		cerr<<"ERROR:  Too many errors entering the size of the board";
		exit (1);			//Terminates Program
	}

	//User input for rows in board is complete
}



//***********************************************************
//Definition of setPlayerTurn								*
//The parameter turns is the number of turns in the game	*
//The function will use that value to determine if it		*
//is White or Reds turn										*
//***********************************************************
int setPlayerTurn(int turns)
{
	if ((turns % 2) == 1)			
	{
		return WHITEPLAYER;			//When turns counter is odd, it is white player's turn
	}
	else
	{
		return REDPLAYER;			//When turns counter is even, it is red player's turn
	}
}



//***************************************************************
//Definition of noMoreMoves										*
//This function is called when there are no more moves possible	*
//The function will determine whos turn it is and decide what	*
//player won based on whose turn it is.							*
//The function prints a message and terminates the program		*
//***************************************************************
void noMoreMoves(int playerTurn)
{
	//Declare Local Variables
	string playerW = " ";
	string playerL = " ";
	char endGameChar = ' ';
	
	if (playerTurn == WHITEPLAYER)				//If white can't move
	{
		playerW = "Red";						//Red wins
		playerL = "White";						//White loses
	}
	else										//If Red can't move
	{								
		playerW = "White";						//White wins
		playerL = "Red";						//Red loses
	}
	cout<<playerL<<" is unable to move"<<endl;				//Print message indicating why
	cout<<"GAME OVER, "<<playerW<<" has won"<<endl;			//game is ending
	cout<<"Enter any character to close the game"<<endl;
	cin>>endGameChar;
	exit (0);												//Exit program
}



//***********************************************************************
//Definition of checkerSelect											*
//The function will prompt the user for a checker to move				*
//The function will then validate the user input type and ensure the 	*
//location contians a checker, is their own checker and is on the board	*
//The function returns a boolean value depending on the validity of the *
//location selected by the user											*
//***********************************************************************
bool checkerSelect(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int &checkerSquare, int numRowsInBoard, int &yLoc, int &xLoc, int playerTurn)
{
	int totalSquares = 0;
	int playerOccupy = -1;

	cout<<"Enter the square number of the checker you want to move"<<endl;		//Prompt user
	if (!(cin>>checkerSquare))
	{
		cin.clear();					//Clear Flag
		cin.ignore(10000, '\n');		//Clear buffer for 10000 characters or \n
		cerr<<"ERROR:  you did not enter an integer"<<endl<<"Try again"<<endl;
		return false;
	}
			
	totalSquares = numRowsInBoard*numRowsInBoard -1;				//Calculates number of valid locations on board
	if (checkerSquare > totalSquares || checkerSquare < 0)			
	{
		cerr<<"ERROR:  that square is not on the board."<<endl<<"Try again"<<endl;
		return false;	
	}
			
	//Check if piece is occupied by opponent
	yLoc = checkerSquare / numRowsInBoard;							//Will return rounded int equal to row number
	xLoc = checkerSquare % numRowsInBoard;							//Will return remainder of division equal to column number
	playerOccupy = 	CMCheckersBoard[yLoc][xLoc];					//Returns value of piece in location
			
	if (playerTurn == WHITEPLAYER)
	{
		if (playerOccupy == REDSOLDIER || playerOccupy == REDMULE || playerOccupy == REDKING)
		{
			cerr<<"ERROR:  that square contains an opponent’s checker"<<endl<<"Try Again"<<endl;
			return false;	
		}
	}
	else
	{
		if (playerOccupy == WHITESOLDIER || playerOccupy == WHITEMULE || playerOccupy == WHITEKING)
		{
			cerr<<"ERROR:  that square contains an opponent’s checker"<<endl<<"Try Again"<<endl;
			return false;	
		}
	}
			
	//Check if location selected is empty
	if (playerOccupy == 0)				
	{
		cerr<<"ERROR:  that square is empty"<<endl<<"Try again"<<endl;
		return false;			
	}
	
	//If no errors above occur
	return true;
}



//***********************************************************************
//Definition of findOtherJumpers										*
//The function will search through the array contining jumpable pieces	*
//to determine if there are any other pieces that are able to jump		*
//The function will record the location of the pieces that can jump in	*
//the array canJumpRecord which is accessable from the main function	*
//***********************************************************************
void findOtherJumpers( int canJumpRecord[MAX_PIECES], int yIndicesJump[MAX_PIECES], int xIndicesJump[MAX_PIECES], int numRowsInBoard)
{
	int index = 0;

	for (int i = 0; i < numRowsInBoard; i++)			
	{
		if (yIndicesJump[i] != -1)						//If a piece can jump, index will be saved (only need to check one of the indexes since arrays are parallel)
		{
			//Will save piece identifier into canJumpRecord Array 
			canJumpRecord[index] = yIndicesJump[i]*numRowsInBoard + xIndicesJump[i];		//Piece location number is calculated by this equation
			index++;
		}
		else
		{
			break;		//Once the first -1 value is reached all values beyond it will also be -1. No need to check
		}				
	}
}



//***********************************************************************
//Definition of moveToSelect											*
//The function will prompt the location to move the checker to			*
//The function will then validate the user input type and ensure the 	*
//location does not contians a checker and is on the board				*
//The function returns a boolean value depending on the validity of the *
//location selected by the user											*
//***********************************************************************
bool moveToSelect(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int &checkerMoveTo, int &yMoveLoc, int &xMoveLoc, int playerTurn)
{
	int totalSquares = 0;
	int playerOccupy = -1;

		cout<<"Enter the square number of the square you want to move your checker to"<<endl;			//Prompt user
		if (!(cin>>checkerMoveTo))			//Check if input is not integer
		{
			cin.clear();					//Clear Flag
			cin.ignore(10000, '\n');		//Clear buffer for 10000 characters or \n
			cerr<<"ERROR:  you did not enter an integer"<<endl<<"Try again"<<endl;
			return false;
		}
			
		totalSquares = numRowsInBoard*numRowsInBoard -1;				//Calculates number of valid locations on board
		if (checkerMoveTo > totalSquares || checkerMoveTo < 0)
		{
			cerr<<"ERROR:  It is not possible to move to a square that is not on the board. "<<endl<<"Try again"<<endl;
			return false;			
		}
			
		//Check if location is occupied
		yMoveLoc = checkerMoveTo / numRowsInBoard;							//Will return rounded int equal to row number
		xMoveLoc = checkerMoveTo % numRowsInBoard;							//Will return remainder of division equal to column number
		playerOccupy = 	CMCheckersBoard[yMoveLoc][xMoveLoc];				//Returns value of piece in location

		if (playerOccupy != 0)			//If no piece on location value will be 0
		{
			cerr<<"ERROR:  that square contains an opponent’s checker"<<endl<<"Try Again"<<endl;
			return false;	
		}
		
		return true;			//If no errors occur return true
}



//*******************************************************************************
//Definition of shouldJump														*
//This function will determine if a piece which must jump is directed to move	*
//The function determines the possible moves the piece could make				*
//The function then tests the move selection against the parameters				*
//The function will print an error message if the piece is directed to move		*
//*******************************************************************************
bool shouldJump (int checkerSquare, int checkerMoveTo, int numRowsInBoard)
{
	int upMove1 = 0;
	int upMove2 = 0;
	int downMove1 = 0;
	int downMove2 = 0;
	int specialMove1 = 0;
	int specialMove2 = 0;
	int specialMove3 = 0;
	int specialMove4 = 0;


	//Set move parameters
	downMove1 = checkerSquare + numRowsInBoard - 1;				//Check down diagonal to left 
	downMove2 = checkerSquare + numRowsInBoard + 1;				//Check down diagonal to right 
	upMove1 = checkerSquare - numRowsInBoard - 1;				//Check up diagonal to left 
	upMove2 = checkerSquare - numRowsInBoard + 1;				//Check up diagonal to right
	specialMove1 = checkerSquare + 1;							//Check across the board
	specialMove2 = checkerSquare - 1;
	specialMove3 = checkerSquare + (2*numRowsInBoard) - 1;
	specialMove4 = checkerSquare - (2*numRowsInBoard) + 1;

	//Check if it is moved location is one of valid move parameters
	if (checkerMoveTo == downMove1 || checkerMoveTo == downMove2 || checkerMoveTo == upMove1 || checkerMoveTo == upMove2)
	{
		cerr<<"ERROR:  You can jump with this checker, you must jump not move 1 space"<<endl<<"Try Again"<<endl;
		return false;
	}
	//If none of the above parameters match then check the speical cases
	else if (checkerMoveTo == specialMove1 || checkerMoveTo == specialMove2 || checkerMoveTo == specialMove3 || checkerMoveTo == specialMove4)
	{
		cerr<<"ERROR:  You can jump with this checker, you must jump not move 1 space"<<endl<<"Try Again"<<endl;
		return false;
	}
	else 
	{
		return true;
	}
}



//***********************************************************************
//Definition of moveToSelectAgain										*
//The function is called when a player can jump again after jumping once*
//The function will accept an input after a prompt is given from main 	*
//The input is tested to ensure it is an integer and in a valid range	*
//The function returns a boolean value depending on the validity of the *
//location selected by the user											*
//***********************************************************************
bool moveToSelectAgain(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int &checkerMoveTo, int &yMoveLoc, int &xMoveLoc, int playerTurn)
{
	int totalSquares = 0;
	int playerOccupy = -1;

		if (!(cin>>checkerMoveTo))			//Check if input is not integer
		{
			cin.clear();					//Clear Flag
			cin.ignore(10000, '\n');		//Clear buffer for 10000 characters or \n
			cerr<<"ERROR:  you did not enter an integer"<<endl<<"Try again"<<endl;
			return false;
		}
			
		totalSquares = numRowsInBoard*numRowsInBoard -1;				//Calculates number of valid locations on board
		if (checkerMoveTo > totalSquares || checkerMoveTo < 0)
		{
			cerr<<"ERROR:  It is not possible to move to a square that is not on the board. "<<endl<<"Try again"<<endl;
			return false;			
		}
			
		//Check if location is occupied
		yMoveLoc = checkerMoveTo / numRowsInBoard;							//Will return rounded int equal to row number
		xMoveLoc = checkerMoveTo % numRowsInBoard;							//Will return remainder of division equal to column number
		playerOccupy = 	CMCheckersBoard[yMoveLoc][xMoveLoc];				//Returns value of piece in location

		if (playerOccupy != 0)			//If no piece on location value will be 0
		{
			cerr<<"ERROR:  that square contains an opponent’s checker"<<endl<<"Try Again"<<endl;
			return false;	
		}
		
		return true;			//If no errors occurr return true
}





//********************************************************************************
//This group of definitions is to determine if the user can move their piece     *
//to an adjacent location														 *
//The fuctions will be called from the IsMovesSquares function					 *
//These functions will determine the location that the checker could move to     *
//Then they will all call the checkLocation function that will determine if the  *
//space the checker will move to is open										 *
//********************************************************************************
bool moveDownLeft (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc)
{
	bool locationEmpty = false;

	xLoc = xLoc - 1; //Calculates the place in the array that the piece would move to if it moved down and leftward
	yLoc = yLoc + 1;

	locationEmpty = checkLocation(CMCheckerBoard, xLoc, yLoc);

	return locationEmpty;
}


bool moveDownRight (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc)
{
	bool locationEmpty = false;

	xLoc = xLoc + 1; //Calculates the place in the array that the piece would move to if it moved down and to the right
	yLoc = yLoc + 1;

	locationEmpty = checkLocation(CMCheckerBoard, xLoc, yLoc);

	return locationEmpty;
}


bool moveUpLeft (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc)
{
	bool locationEmpty = false;

	xLoc = xLoc - 1; //Calculates the place in the array that the piece would move to if it moved up and to the left
	yLoc = yLoc - 1;

	locationEmpty = checkLocation(CMCheckerBoard, xLoc, yLoc);

	return locationEmpty;
}


bool moveUpRight (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc)
{
	bool locationEmpty = false;

	xLoc = xLoc + 1; //Calculates the place in the array that the piece would move to if it moved up and to the right
	yLoc = yLoc - 1;

	locationEmpty = checkLocation(CMCheckerBoard, xLoc, yLoc);

	return locationEmpty;
}


bool wrapAroundRightUp (int CMCheckerBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc, int numRows)
{
	bool locationEmpty = false;

	xLoc = xLoc - (numRows-1); //Calculates the place in the array that the piece would move to if it moved around the board and up one row
	yLoc = yLoc - 1;

	locationEmpty = checkLocation(CMCheckerBoard, xLoc, yLoc);

	return locationEmpty;
}


bool wrapAroundLeftUp (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc, int numRows)
{
	bool locationEmpty = false;

	xLoc = xLoc + (numRows - 1); //Calculates the place in the array that the piece would move to if it moved around the board and up one row
	yLoc = yLoc - 1;

	locationEmpty = checkLocation(CMCheckerBoard, xLoc, yLoc);

	return locationEmpty;
}


bool wrapAroundRightDown (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc, int numRows)
{
	bool locationEmpty = false;

	xLoc = xLoc - (numRows - 1); //Calculates the place in the array that the piece would move to if it moved around the board and down one row
	yLoc = yLoc + 1;

	locationEmpty = checkLocation(CMCheckerBoard, xLoc, yLoc);

	return locationEmpty;
}


bool wrapAroundLeftDown (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int xLoc, int yLoc, int numRows)
{
	bool locationEmpty = false;

	xLoc = xLoc + (numRows - 1); //Calculates the place in the array that the piece would move to if it moved around the board and up one row
	yLoc = yLoc + 1;

	locationEmpty = checkLocation(CMCheckerBoard, xLoc, yLoc);

	return locationEmpty;
}

//***********************************************************
//Checks if the location of the sqaure given into it is	    *
//filled with a piece or not	       						*
//***********************************************************
bool checkLocation (int CMCheckerBoard [MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int potentialX, int potentialY)
{
	int pieceValue = CMCheckerBoard [potentialY][potentialX];

	if (pieceValue != 0)
	{
		return false; //Some piece is already there
	}
	else 
	{
		return true; //Space is free
	}
}



//*****************************************************************
//This function checks what piece is on the given square and      *
//returns its value.                                              *
//*****************************************************************
int checkerValueOnSquare (int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int yLoc, int xLoc)
{
	int value = -1;

	value = CMCheckersBoard[yLoc][xLoc];

	return value;
}