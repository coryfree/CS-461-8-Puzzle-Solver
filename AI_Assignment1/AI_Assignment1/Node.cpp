#include "Node.h"

//constructor that needs to be passed an array of the puzzle state and the g value
Node::Node(int a[3][3], int g) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			puzzleArray[i][j] = a[i][j]; //sets the puzzleArray
		}
	}
	int answerArray[3][3] = { {1,2,3} , {4,5,6} , {7,8,0} }; //sets the answer array
	findBlank(); //calls the findBlank function so the blank i and blank j values are set
	pieceVal = 10; //default sets this to 10, gets changed later
	direction = 0; //default sets this to 0, gets changed later
	gVal = g; //sets the g value to whatever is passed
}

//iterates through the puzzle state until it hits the blank tile
//then sets the blank_i and blank_j values
void Node::findBlank() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (puzzleArray[i][j] == 0) {
				blank_i = i;
				blank_j = j;
			}
		}
	}
}

//returns true the i value and j value give a valid location in a 3 x 3 array
bool Node::validMove(int iValue, int jValue) {
	if ((iValue <= 2 && iValue >= 0) && (jValue <= 2 && jValue >= 0))
		return true;
	else
		return false;
}



