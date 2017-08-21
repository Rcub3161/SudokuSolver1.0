#ifndef _ROW_H_
#define _ROW_H_
#include <iostream>
#include <stdlib.h>
#include <vector>
class Row {
private:

public:
	int rowNumber;
	std::vector<int> rowVector;
	void printRow();
};


#endif // !_ROW_H_
