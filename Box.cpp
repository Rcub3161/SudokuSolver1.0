#include "Box.h"
using namespace std;

Box::Box(int rowNum, int colNum, int netNum, int val, int boxNum, bool fix) {
	rowNumber = rowNum;
	colNumber = colNum;	
	netNumber = netNum;
	value = val;
	fixed = fix;
}

void Box::setValue(int val) {
	value = val;
}