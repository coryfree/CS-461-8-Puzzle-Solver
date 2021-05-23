#pragma once

#include <vector>
#include <functional>
#include <iostream>
#include <queue>
using namespace std;

//creates a class that will be used to store puzzle states
class Node
{
private: 
	int answerArray[3][3]; //this is the solution array for each puzzle

public:
	Node(int a[3][3], int g); //constructor that sets the gVal and puzzleArray
	int puzzleArray[3][3]; //stores the actual array for each different puzzle
	int pieceVal; //which value is at each tile
	int direction; //tells the program which direction is moved when new states are made
	int gVal; //tells the depth that the puzzle was made at
	int blank_i; //stores the i value of the blank tile
	int blank_j; //stores the j value of the blank tile
	void findBlank(); //function that sets the blank_i and blank_j values
	bool validMove(int iValue, int jValue); //returns true if the i value and j value passed in are in the scope of a 3 by 3 array
};
