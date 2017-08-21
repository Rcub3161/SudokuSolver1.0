#ifndef _NET_H_
#define _NET_H_

#include <iostream>
#include <stdlib.h>
#include <vector>

class Net {
	private:

	public:
		int netNumber;
		std::vector<int> netVector;
		void removeFromNetArray(int val);
		void addToNetArray(int val);
		void printNet();
};


#endif // !_NET_H_
