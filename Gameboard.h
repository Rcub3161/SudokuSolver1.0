#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "Net.h"
#include "Row.h"
#include "Column.h"
#include "Box.h"

class Gameboard {
private:
public:
	Gameboard();
	std::vector<int> removeFromVector(std::vector<int> vec, int val);
	int currentBox;
	std::vector<Box> boxesVector;
	std::vector<Row> rowsVector;
	std::vector<Column> columnsVector;
	std::vector<Net> netsVector;
	void buildBoard();
	int determineNetNumber(int currentRow, int currentColumn);
	void printBoard();
	bool solveBoard(Box box);
	void printRows();
	void printColumns();
	void printNets();
	std::vector<int> getValidValuesForBox(Box box);
	std::vector<int> removeDoubleValues(std::vector<int> vec1, std::vector<int> vec2);
	void addToRow(int rowNumber, int value);
	void addToColumn(int columnNumber, int value);
	void addToNet(int netNumber, int value);
	void removeFromRow(int rowNumber, int value);
	void removeFromColumn(int columnNumber, int value);
	void removeFromNet(int netNumber, int value);

};

#endif //!_GAMEBOARD_H