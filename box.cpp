//Zack Santora 
/*
add try and catch 
figure out how to end the game 
rework notes
//This is a program that simulates a one person game of Shut the Box.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctype.h>
#include <array>
#include "termmanip.h"
#include "box.h"
#include <unistd.h>

using namespace std;

int main()
{
	srand( time( NULL ) );
	int playerBoard[9] = {0};// the board of nine boxes  
	int answer = -1; //The users decision to see the instructions, to play with the two numbers they rolled or the combined total 
	int die1 = 0; // The number rolled on the first die
	int die2 = 0; // The number rolled on the second die
    bool doubles, gameOver;// if the die are the same 
	int dieTotal = 0; // The number that is the result of the die being added
	int turnTotal = 0; // the number of rolls the player made
    char prompt, param;
    int choice;
    
	cout << " WELCOME TO SHUT THE BOX " << endl;
    
    cout << "Would you like to learn the rules of the game?"<< endl;
        cout << "  1. Yes " << endl;
        cout << "  2. No " << endl;
	cin >> answer;
	cout << endl;

	if (answer == 1 )
	{
		displayInstructions( );
        printBoard(playerBoard);
        cout << " Would you like to play? " << endl;
        cout << " 1.) Yes lets play " << endl << " 2.) No get me heck outta here " << endl;
        cin >> choice;
        if(choice == 1){
            answer = 2;
        }else if(choice == 2){
            exit(0);
        }
    }
	while(answer == 2)
	{
    int totalRolls;
	bool doubles = false;//vairable for finding doubles in dice roll
	cout << endl;

	totalRolls = 0;
	while (gameOver == false)
	{
        cout << clearScreen << cursorPosition(0,0) << cursorOff;
        cout.flush();
        printBoard(playerBoard);
		generateDiceNumbers( die1, die2, doubles, prompt);
		totalRolls++;	//counter for dice rolls
		if (playerBoard[die1 - 1] > 0)						//checks for open or shut boxes
		{
			playerBoard[die1 - 1] = 0;
		}
		else
		{
			playerBoard[die1 - 1] = (die1);
		}
		if ((die2 > 0)&& (playerBoard[die2 -1] > 0))		//checks for open or shut boxes
		{ 
			playerBoard[die2 - 1] = 0;
		}
		else
		{
			playerBoard[die2 - 1] = (die2);
		}
    gameOver = gameOverCheck(playerBoard, gameOver, totalRolls);
        
    }
        
    return 0;
}
}

/*displayInstructions: This function opens an input file stream, reads the file and displays the instructions, then closes the file stream*/
void displayInstructions( )
{
	string instructions; // string that contains input from instruction file
	ifstream inputFile;
	inputFile.open( "shutTheBoxInstructions.txt" );
	if ( !inputFile )
	{
		cout << "Input Failed, Exiting Program" << endl;
		system( "pause" );
		exit( 1 );
	}
	while ( !inputFile.eof( ) )
	{
		getline( inputFile, instructions );
		cout << instructions << endl;
	}
	inputFile.close( );
}

/*generateDiceNumber: This function generates two random numbers, one for each die.
randomNum1: The variable in the function that die1 is passed by reference to die1
randomNum2: The variable in the function that die2 is passed by reference to die2 */
void generateDiceNumbers(int &die1, int &die2, bool &doubles, char prompt)
{
    doubles = false;
	die1 = rand() % 6 + 1;
	die2 = rand() % 6 + 1;
    int dietotal;
    int i;

    dietotal = die1 + die2;

	if (die1 == die2)
	{
		doubles = true;
	}
	cout << "Rolled " << die1 << " and " << die2 << "." << endl;

	//this block to check the sum range for random roll, cannot exceed 2-9 range
	if ((die1 + die2) > 9)
	{
		cout << "Dice sum is greater than board, can only use individual rolls." << endl;
        cout << dietotal << endl;
        cout << usleep(50000);
        
	}
	else
	{
        cout << reverseVideo << "**Any rolls totaling above nine the indidvicual numbres are atumatically used** " << endl;
		cout << normal << "Use sum of the dice or individual numbers? " << endl << "1. Dice Total: " << dietotal << endl;
        cout << "2. Individual Numbers" << endl;
        cout << "3. To exit " << endl;
		cin >> i;
		switch (i)
		{
            case 1: die1 = die1 + die2;
                    die2= -1;
        break;
            case 2: die1 || die2;
        break;
            case 3: exit(0);
        break;
        }
	}
}

//Prints the board and displays the open and closed boxes

void printBoard( int playerBoard[] )
{
    for (int i = 0; i < 9; i++)
	{		//block for top parts of open box lids and open air
		if ((i <= 0) && (playerBoard[i] > 0)) { cout << red << "__________ "; }
		if ((i > 0) && (playerBoard[i] > 0)) { cout << red << "__________ "; }
		if ((i <= 0) && (playerBoard[i] < 1)) { cout << "           "; }
		if ((i > 0) && (playerBoard[i] < 1)) { cout << "           "; }
	}
	cout << endl;
     
	 for (int i = 0; i < 9; i++)
		{		//block for middle parts of open box lids and open air
			if ((i <= 0) && (playerBoard[i] > 0)) { cout << red << bold << "| CLOSED | "; }
			if ((i > 0) && (playerBoard[i] > 0)) { cout << red << bold << "| CLOSED | "; }
			if ((i <= 0) && (playerBoard[i] < 1)) { cout << "           "; }
			if ((i > 0) && (playerBoard[i] < 1)) { cout << "           "; }
		}
		cout << normal << endl;
	cout << reverseVideo;
	cout << "|        | |        | |        | |        | |        | |        | |        | |        | |        | " << endl;
    cout << "|   1    | |    2   | |   3    | |   4    | |   5    | |   6    | |   7    | |   8    | |   9    | " << endl;
	cout << "|________| |________| |________| |________| |________| |________| |________| |________| |________| " << endl;
	cout << normal << endl;
    }

//The game is all over
bool gameOverCheck(int playerBoard[], bool gameOver, int totalRolls )
{
	int closedAmount = 0; //How many boxes are closed currently?
	for ( int i = 0; i < 9; i++ )
	{
		if ( playerBoard[i] > 0)
		{
			closedAmount++;
		}
	}
	if ( closedAmount == 9 )
	{
		gameOver = true;
		cout << "ALL THE BOXES CLOSED!" << endl;
        cout << "Your score is " << totalRolls << endl;
	}
	return gameOver;
}
