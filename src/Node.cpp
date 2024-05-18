#include "Node.h" 

Node::Node(){

}

void Node::copyArray(int GameArray[][7]){
for (int i =0;i<6;++i)
	for(int j = 0; j<7 ; ++j)
		this->GameArray[i][j] = GameArray[i][j];
return;
}
