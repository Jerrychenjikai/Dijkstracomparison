#include <iostream>
#include <cstring>
#include "node.h"
#define maxn 200005
using namespace std;

class priorityq{
private:
	node* nodes[maxn];
	bool deleted[maxn];
	int top=0;
	int cnt=0;
	int minn=2147483647;
	int minmark;

public:
	priorityq(){
		memset(deleted,0,sizeof(deleted));
	}
	
	void push(node& a){
		nodes[a.id]=&a;
		top=max(top,a.id);
	}
	
	void change(node& a,int value){
		if(a.value>value) a.value=value;
	}
	
	void del(){
		minn=2147483647;
		for(int i=1;i<=top;i++){
			if(minn>nodes[i]->value and !deleted[i]){
				minn=nodes[i]->value;
				minmark=i;
			}
		}
		
		deleted[minmark]=1;
		cnt++;
	}
	
	node& front(){
		minn=2147483647;
		for(int i=1;i<=top;i++){
			if(minn>nodes[i]->value and !deleted[i]){
				minn=nodes[i]->value;
				minmark=i;
			}
		}
		
		return *nodes[minmark];
	}
	
	bool empty(){
		if(cnt==top) return 1;
		return 0;
	}
};