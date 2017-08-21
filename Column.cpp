using namespace std;
#include "Column.h"

void Column::printColumn() {
	for (int i = 0; i < columnVector.size(); i++) {
		cout << columnVector[i] << endl;
	}
}
