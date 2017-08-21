#ifndef _BOX_H_
#define _BOX_H
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

class Box {
	private:

	public: 
		Box(int rowNum, int colNum, int netNum, int val, int boxNum, bool fixed);
		int boxNumber;
		int rowNumber;
		int colNumber;
		int netNumber;
		int value;
		bool fixed;
		void setValue(int val);
};



#endif // !_BOX_H
