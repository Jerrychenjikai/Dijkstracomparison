#ifndef NODE
#define NODE
#include <vector>
using namespace std;

struct heapnode;

struct node{
	int id;                   //should be stored as an array, their position is their id
	vector<int> sides;        //destination node
	vector<int> cost;         //cost of the side
	int value=2147483647;        //distance from root node to this node
	heapnode* heaphandle=nullptr;
	
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
