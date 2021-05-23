//Cory Free
//Program 1
//Intro to AI
//February 9th 2020

#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "Node.h"
using namespace std;

//this function simply outputs whatever array is passed to it
//mostly used for testing
void printA(int d[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << d[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

//returns true if the two arrays passed in are equal, returns false if they are not equal
//used to determine which arrays have been visted before
bool equalArrays(int a[3][3], int b[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (a[i][j] != b[i][j]) {
				return false;
			}
		}
	}
	return true;
}

// returns true if the given array is already in the vector with all the previous attempts
bool previouslyAttempted(vector<Node> v, int newAttempt[3][3]) {
	for (int i = 0; i < v.size(); i++) {
		if (equalArrays(v[i].puzzleArray, newAttempt)) {
			return true;
		}
	}
	return false;
}

//returns the number of inversions within each puzzle
//used to determine if a puzzle is solvable before trying to solve it
int inversionNum(int a[]) {
	int inv = 0;
	for (int i = 0; i < 9 - 1; i++) {
		for (int j = i + 1; j < 9; j++) {
			if (a[j] && a[i] && a[i] > a[j]) {
				inv++;
			}
		}
	}
	return inv;
}

//returns true if the given puzzle is solvable 
bool solvable(int a[3][3]) {
	// returns the number of inversion for a given puzzle 
	int invNum = inversionNum((int *)a);

	// if the inversion number is even, then it is solvable so it returns true
	// if the inversion number is odd, then it returns false because it is not solvable
	return (invNum % 2 == 0);
}

//function that returns the manhattan cost (city block value) of the array that is passed in
int findManhattanCost(int a[3][3]) {
	int cost = 0;
	int answerArray[3][3] = { {1,2,3} , {4,5,6} , {7,8,0} }; //sets the goal array
	for (int i = 0; i < 3; i++) //iterate through the array
	{
		for (int j = 0; j < 3; j++)
		{
			if (a[i][j] != 0) //if the piece is the blank square, it has no manhattan value
			{
				for (int k = 0; k < 3; k++)
				{
					for (int l = 0; l < 3; l++)
					{
						if (a[i][j] == answerArray[k][l])
							cost += abs(i - k) + abs(j - l); //add the number of squares away it is
					}
				}
			}
		}
	}
	return cost;
}

//struct that compares the manhattan values of the two Nodes, plus the g value
//used to determine which item in the priority queue should be on top
struct compareManhattanValues
{
	bool operator() (Node &a, Node &b)
	{
		int aMan =  findManhattanCost(a.puzzleArray) + a.gVal;
		int bMan = findManhattanCost(b.puzzleArray) + b.gVal;
		return aMan > bMan;
	}
};

//returns true if the puzzle has been solved
//compares each item in the array to the solution array
bool isComplete(int attempt[3][3]) {
	int answerArray[3][3] = { {1,2,3} , {4,5,6} , {7,8,0} };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (attempt[i][j] != answerArray[i][j]) {
				return false;
			}
		}
	}
	return true;
}

//function that takes in a vector of Nodes and prints out each node's puzzle
//mostly used for testing
void printVector(vector<Node> v) {
	for (int i = 0; i < v.size(); i++) {
		printA(v[i].puzzleArray);
	}
}

//function that returns a vector of type Node, takes in a Node and the location of the blank tile
//returns a vector with all the possible moves from the given position
vector<Node> findValidMoves(Node a, int iValue, int jValue) {
	vector<Node> neighbors; //create a vector that will be returned at the end
	int tempArray[3][3]; //sets a temporary array to the same values of the given Node
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tempArray[i][j] = a.puzzleArray[i][j];
		}
	}
	//checks if subtracting 1 from the i value of the zero tile would be a valid move
	if (a.validMove(iValue - 1, jValue)) {
		swap(tempArray[iValue][jValue], tempArray[iValue - 1][jValue]); //if it is a valid move, swap that value with the zero value
		Node up(tempArray, a.gVal + 1); //create a node with the new puzzle state (adding 1 to the g value)
		up.pieceVal = tempArray[iValue][jValue];  //sets which value is being moved in this puzzle state
		up.direction = 1; //sets the direction value so that I can output which direction is moved later
		neighbors.push_back(up); //push this puzzle state into the vector I created
		swap(tempArray[iValue][jValue], tempArray[iValue - 1][jValue]); //swap the values back to their original places 
	}
	//repeat the same thing, adding one to the i value this time
	if (a.validMove(iValue + 1, jValue)) {
		swap(tempArray[iValue][jValue], tempArray[iValue + 1][jValue]);
		Node down(tempArray, a.gVal + 1);
		down.pieceVal = tempArray[iValue][jValue];
		down.direction = 2;
		neighbors.push_back(down);
		swap(tempArray[iValue][jValue], tempArray[iValue + 1][jValue]);
	}
	//repeat the same thing, subtracting one from the j value
	if (a.validMove(iValue, jValue - 1)) {
		swap(tempArray[iValue][jValue], tempArray[iValue][jValue - 1]);
		Node left(tempArray, a.gVal + 1);
		left.pieceVal = tempArray[iValue][jValue];
		left.direction = 3;
		neighbors.push_back(left);
		swap(tempArray[iValue][jValue], tempArray[iValue][jValue - 1]);
	}
	//repeat the same thing, adding one to the j value
	if (a.validMove(iValue, jValue + 1)) {
		swap(tempArray[iValue][jValue], tempArray[iValue][jValue + 1]);
		Node right(tempArray, a.gVal + 1);
		right.pieceVal = tempArray[iValue][jValue];
		right.direction = 4;
		neighbors.push_back(right);
		swap(tempArray[iValue][jValue], tempArray[iValue][jValue + 1]);
	}
	return neighbors; //return the vector with all the possible moves
}

int main() {
	ifstream fin("program_1_data.txt"); //create an in stream for the input file
	ofstream fout("output.txt"); //create an out stream for the output file
	int puzzle[3][3]; //2 dimensional array to store each puzzle that is read in
	int puzzlenum = 1;
	string outputString = ""; //string that I push all the moves into, to make it easier to output
	vector<Node> neighborsArray; //vector full of Nodes that has puzzles of possible moves
	vector<Node> previousAttempts; //vector full of Nodes of puzzles that have already been visited

	//reads in the data into the puzzle array, the loop stops when there are no more puzzles
	while (fin >> puzzle[0][0]) {
		fin >> puzzle[0][1];
		fin >> puzzle[0][2];
		fin >> puzzle[1][0];
		fin >> puzzle[1][1];
		fin >> puzzle[1][2];
		fin >> puzzle[2][0];
		fin >> puzzle[2][1];
		fin >> puzzle[2][2];
		int solved = 0; //value that becomes 1 if the puzzle is solved
		int gValue = 0; //value that keeps track of the g value of each puzzle
		int iterations = 0; //keeps track of the number of iterations
		outputString.append("Solving puzzle number ");
		outputString.append(to_string(puzzlenum));
		outputString.append(":\n\n");

		Node state(puzzle, gValue); //creates a new object of the Node class to push into the queue

		priority_queue<Node, vector<Node>, compareManhattanValues > nextPuzzle; //declares the priority queue that keeps all the puzzles
		
		//checks if the puzzle is solvable before iterating through all the possible moves
		if (solvable(state.puzzleArray)) {
			nextPuzzle.push(state); //if it is solvable, push the Node into the queue
		}

		//a loop that keeps going while there are items in the queue
		while (!nextPuzzle.empty()) {
			//sets a temporary array equal to the top item of the queue
			int tempA[3][3];
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					tempA[i][j] = nextPuzzle.top().puzzleArray[i][j];
				}
			}
			
			//starts to output the direction and piece moved after the first iteration
			if (iterations > 0) {
				if (nextPuzzle.top().direction == 2) { //checks which direction the piece was moved
					outputString.append("Moving the ");
					outputString.append(to_string(nextPuzzle.top().pieceVal));
					outputString.append(" piece up...\n");
				}
				if (nextPuzzle.top().direction == 1) {
					outputString.append("Moving the ");
					outputString.append(to_string(nextPuzzle.top().pieceVal));
					outputString.append(" piece down...\n");
				}
				if (nextPuzzle.top().direction == 4) {
					outputString.append("Moving the ");
					outputString.append(to_string(nextPuzzle.top().pieceVal));
					outputString.append(" piece left...\n");
				}
				if (nextPuzzle.top().direction == 3) {
					outputString.append("Moving the ");
					outputString.append(to_string(nextPuzzle.top().pieceVal));
					outputString.append(" piece right...\n");
				}
			}
			//only goes into this else statement on the first iteration
			//outputs the starting position of the puzzle
			else {
				outputString.append("Starting position: \n");
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						outputString.append(to_string(tempA[i][j]));
						outputString.append(" ");
					}
					outputString.append("\n");
				}
				outputString.append("\n");
			}

			//pop the top item in the queue
			nextPuzzle.pop();

			//create a new object of Node with the temporary array I just initialized
			Node temp(tempA, gValue);
			previousAttempts.push_back(temp); // push it into the previously attempted vector

			//checks if the current array being evaluated is the goal
			if (isComplete(temp.puzzleArray)) {
				solved = 1; //change solved to 1
				for (int i = 0; i < 3; i++) { //output the finished puzzle
					for (int j = 0; j < 3; j++) {
						outputString.append(to_string(temp.puzzleArray[i][j]));
						outputString.append(" ");
					}
					outputString.append("\n");
				}
				outputString.append("\nPuzzle ");
				outputString.append(to_string(puzzlenum));
				outputString.append(" has been solved in ");
				outputString.append(to_string(iterations));
				outputString.append(" moves.\n");
				break; //end the while loop to start the next puzzle
			}

			//calls the findValidMoves function and puts the possible moves in the neighborsArray
			neighborsArray = findValidMoves(temp, temp.blank_i, temp.blank_j);
			
			//iterate through the neighborsArray
			//if the iteration is not in the previousAttempts array then push it into the queue
			for (int i = 0; i < neighborsArray.size(); i++) {
				if (!previouslyAttempted(previousAttempts, neighborsArray[i].puzzleArray)) { 
					nextPuzzle.push(neighborsArray[i]);
				}
			}
			iterations++; //incrememnt iterations
		}
		//if the puzzle was not solved, output that it was not solved
		if(solved != 1) {
			outputString.append("Puzzle ");
			outputString.append(to_string(puzzlenum));
			outputString.append(" could not be solved\n");
		}
		
		outputString.append("-------------------------\n\n");
		previousAttempts.clear(); //clear the previous attempts vector
		puzzlenum++; //increment the number of which puzzle is being solved
	}
	fout << outputString; //output the string with all the answers
	system("pause");
	return 0;
}