// SudokuSolver3.0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Gameboard.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;
int main()
{
	Gameboard board = Gameboard();
	board.buildBoard();
	board.printBoard();
	board.printRows();
	cout << "-------------------------------" << endl;
	board.printColumns();
	cout << "-------------------------------";
	board.printNets();
	board.solveBoard(board.boxesVector[board.currentBox]);
	board.printBoard();
    return 0;
}

