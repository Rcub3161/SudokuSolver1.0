using namespace std;
#include "Row.h"

void Row::printRow() {
	for (int i = 0; i < rowVector.size(); i++) {
		cout << rowVector[i] << " " << endl;
	}
}
