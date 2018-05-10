#define BOX_H


void displayInstructions( );// displays the game instructions
void generateDiceNumbers( int &die1, int &die2, bool &doubles, char prompt);// generates random numbers for the "rolled" die
bool gameOverCheck(int playerBoard[], bool gameOver, int totalRolls);
void printBoard( int playerBoard[] );// prints the contents of the playerBoard array with an index above 
