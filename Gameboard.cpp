#include "Gameboard.h"
using namespace std;

void Gameboard::buildBoard() {
	int currentRow = 0;
	int currentNet = 0;
	int boxNumber = 0;
	int currentColumn;
	int currentValue;
	cout << "Please enter your board. Starting with the top left net and top left box. If unknown enter 0" << endl;
	while (currentRow < 9) {
		Row newRow = Row();
		Column newColumn = Column();
		Net newNet = Net();
		rowsVector.push_back(newRow);
		columnsVector.push_back(newColumn);
		netsVector.push_back(newNet);
		for (int i = 0; i < 9; i++) {
			cin >> currentValue;
			currentColumn = i;
			currentNet = determineNetNumber(currentRow, currentColumn);
			if (currentValue == 0) {
				Box newBox(currentRow, currentColumn, currentNet, currentValue, boxNumber, false);
				boxesVector.push_back(newBox);
				boxNumber++;
			}
			else {
				Box newBox(currentRow, currentColumn, currentNet, currentValue, boxNumber, true);
				boxesVector.push_back(newBox);
				boxNumber++;
			}
		}
		currentRow++;
	}
	for (int i = 0; i < boxesVector.size(); i++) {
		if (boxesVector[i].value != 0) {
			rowsVector[boxesVector[i].rowNumber].rowVector.push_back(boxesVector[i].value);
			columnsVector[boxesVector[i].colNumber].columnVector.push_back(boxesVector[i].value);
			netsVector[boxesVector[i].netNumber].netVector.push_back(boxesVector[i].value);
		}
	}
}

Gameboard::Gameboard() {
	currentBox = 0;
}

int Gameboard::determineNetNumber(int currentRow, int currentColumn) {
	int netNumber = -1;
	if (currentRow >= 0 && currentRow < 3) {
		if (currentColumn >= 0 && currentColumn < 3) {
			netNumber = 0;
		}
		else if (currentColumn >= 3 && currentColumn < 6) {
			netNumber = 1;
		}
		else if (currentColumn >= 6 && currentColumn < 9) {
			netNumber = 2;
		}
		else {
			cout << "ERROR" << endl;
		}
	}
	else if (currentRow >= 3 && currentRow < 6) {
		if (currentColumn >= 0 && currentColumn < 3) {
			netNumber = 3;
		}
		else if (currentColumn >= 3 && currentColumn < 6) {
			netNumber = 4;
		}
		else if (currentColumn >= 6 && currentColumn < 9) {
			netNumber = 5;
		}
		else {
			cout << "ERROR" << endl;
		}
	}
	else if (currentRow >= 6 && currentRow < 9) {
		if (currentColumn >= 0 && currentColumn < 3) {
			netNumber = 6;
		}
		else if (currentColumn >= 3 && currentColumn < 6) {
			netNumber = 7;
		}
		else if (currentColumn >= 6 && currentColumn < 9) {
			netNumber = 8;
		}
		else {
			cout << "ERROR" << endl;
		}
	}
	else {
		cout << "ERROR" << endl;
	}
	return netNumber;
}

void Gameboard::printBoard() {
	for (int i = 0; i < boxesVector.size(); i++) {
		if (i % 3 == 0 && i % 9 != 0) {
			cout << "{ " << boxesVector[i].value << " ";
		}
		else if (i % 3 == 2) {
			cout << boxesVector[i].value << " }";
		}
		else if (i % 9 == 0 && i % 3 == 0) {
			cout << endl << "{ " << boxesVector[i].value << " ";
		}
		else {
			cout << boxesVector[i].value << " ";
		}
	}
}

bool Gameboard::solveBoard(Box box) {
	if (currentBox == 80) {
		std::vector<int> validBoxValues = getValidValuesForBox(boxesVector[currentBox]);
		boxesVector[currentBox].value = validBoxValues[0];
		addToRow(box.rowNumber, boxesVector[currentBox].value);//add to row
		addToColumn(box.colNumber, boxesVector[currentBox].value);//add to column
		addToNet(box.netNumber, boxesVector[currentBox].value);//add to net
		return true;
	}
	else if (box.fixed) {
		currentBox += 1;
		bool next = solveBoard(boxesVector[currentBox]);
		if (!next) {
			currentBox -= 1;
			return false;
		}
		else {
			return true;
		}
	}
	else {
		bool solved = false;
		bool reachedMax = false;
		std::vector<int> validBoxValues = getValidValuesForBox(boxesVector[currentBox]);
		if (validBoxValues.size() > 0) {
			for (int i = 0; i < validBoxValues.size(); i++) {
				boxesVector[currentBox].value = validBoxValues[i];
				//box.value = validBoxValues[i];
				addToRow(box.rowNumber, boxesVector[currentBox].value);//add to row
				addToColumn(box.colNumber, boxesVector[currentBox].value);//add to column
				addToNet(box.netNumber, boxesVector[currentBox].value);//add to net
				currentBox++;
				if (solveBoard(boxesVector[currentBox])) {
					solved = true;
					return true;
				}
				else {
					removeFromRow(box.rowNumber, boxesVector[currentBox].value);//remove from row
					removeFromColumn(box.colNumber, boxesVector[currentBox].value);//remove from column
					removeFromNet(box.netNumber, boxesVector[currentBox].value);//remove from net
					boxesVector[currentBox].value = 0;//.value = 0;
				}
				if (i == validBoxValues.size() - 1) {
					reachedMax = true;
				}
			}//if for loop reaches max and box value is 0 we need to decrement currentbox;
			/*if (reachedMax && box.value == 0) {
				currentBox--;
				return false;
			}*/
			if (reachedMax && boxesVector[currentBox].value == 0) {
				currentBox--;
				return false;
			}
			
		}
		else {
			currentBox--;
			return false;
		}
	}
}

void Gameboard::printRows() {
	for (int i = 0; i < rowsVector.size(); i++) {
		rowsVector[i].printRow();
		cout << endl;
	}
}

void Gameboard::printColumns() {
	for (int i = 0; i < columnsVector.size(); i++) {
		columnsVector[i].printColumn();
		cout << endl;
	}
}

void Gameboard::printNets() {
	for (int i = 0; i < netsVector.size(); i++) {
		netsVector[i].printNet();
		cout << endl;
	}
}

std::vector<int> Gameboard::getValidValuesForBox(Box box) {
	std::vector<int> validValues = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	validValues = removeDoubleValues(validValues, rowsVector[box.rowNumber].rowVector);
	validValues = removeDoubleValues(validValues, columnsVector[box.colNumber].columnVector);
	validValues = removeDoubleValues(validValues, netsVector[box.netNumber].netVector);
	return validValues;
}

std::vector<int> Gameboard::removeDoubleValues(std::vector<int> vec1, std::vector<int> vec2) {
	std::vector<int> uncommonValuesVector = vec1;
	bool changed = true;
	for (int i = 0; i < vec1.size(); i++) {
		for (int j = 0; j < vec2.size(); j++) {
			if (vec1[i] == vec2[j]) {
				uncommonValuesVector = removeFromVector(uncommonValuesVector, vec1[i]);
			}
		}
	}

	return uncommonValuesVector;
}

std::vector<int> Gameboard::removeFromVector(std::vector<int> vec, int val) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == val) {
			swap(vec[i], vec.back());
			vec.pop_back();
		}
	}
	return vec;
}

void Gameboard::addToRow(int rowNumber, int value) {
	rowsVector[rowNumber].rowVector.push_back(value);
}
void Gameboard::addToColumn(int columnNumber, int value) {
	columnsVector[columnNumber].columnVector.push_back(value);

}
void Gameboard::addToNet(int netNumber, int value) {
	netsVector[netNumber].netVector.push_back(value);

}
void Gameboard::removeFromRow(int rowNumber, int value) {
	for (int i = 0; i < rowsVector[rowNumber].rowVector.size(); i++) {
		if (rowsVector[rowNumber].rowVector[i] == value) {
			//rowsVector[rowNumber].rowVector.erase(rowsVector[rowNumber].rowVector.begin() + i);
			swap(rowsVector[rowNumber].rowVector[i], rowsVector[rowNumber].rowVector.back());
			rowsVector[rowNumber].rowVector.pop_back();
		}
	}
}
void Gameboard::removeFromColumn(int columnNumber, int value) {
	for (int i = 0; i < columnsVector[columnNumber].columnVector.size(); i++) {
		if (columnsVector[columnNumber].columnVector[i] == value) {
			swap(columnsVector[columnNumber].columnVector[i], columnsVector[columnNumber].columnVector.back());
			columnsVector[columnNumber].columnVector.pop_back();
		}
	}
}
void Gameboard::removeFromNet(int netNumber, int value) {
	for (int i = 0; i < netsVector[netNumber].netVector.size(); i++) {
		if (netsVector[netNumber].netVector[i] == value) {
			swap(netsVector[netNumber].netVector[i], netsVector[netNumber].netVector.back());
			netsVector[netNumber].netVector.pop_back();
		}
	}
}


