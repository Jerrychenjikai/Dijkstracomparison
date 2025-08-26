#ifndef NODE
#define NODE
#include <vector>
using namespace std;

struct heapnode; //defined in implementation of the min-heap

struct node{
	int id;                   //should be stored as an array, their position is their id
	
	//graph structure
	vector<int> sides;        //destination node
	vector<int> cost;         //cost of the side
	
	//distance from root node to this node, otherwise known as its weight
	int value=2147483647;
	heapnode* heaphandle=nullptr;	//link to node of the min heap
	
	//redifine compare operations to compare weight
	
	bool operator < (const node& other) const{
		return value < other.value;
	}
	
	bool operator > (const node& other) const{
		return value > other.value;
	}
	
	bool operator >= (const node& other) const{
		return value >= other.value;
	}
	
	bool operator <= (const node& other) const{
		return value <= other.value;
	}
	
	bool operator == (const node& other) const{
		return value == other.value;
	}
	
	bool operator != (const node& other) const{
		return value != other.value;
	}
};

#endif
