#ifndef NODE
#define NODE

#include <vector>

class Node{

	public:
		std::vector<Node*> child;
		int GameArray [6][7];
		Node();
		void copyArray(int GameArray[][7]);
		int value;

	private:




};


#endif
