#ifndef _COLUMN_H
#define _COLUMN_H
#include <iostream>
#include <stdlib.h>
#include <vector>
class Column {
private:

public:
	int colNumber;
	std::vector<int> columnVector;
	void printColumn();

};

#endif // !_Column_H_
