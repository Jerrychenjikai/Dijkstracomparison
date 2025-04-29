#include <iostream>
#include <vector>
#include "node.h"
#define maxn 2000005
using namespace std;

class priorityq{//small heap
private:
	int id_to_pos[maxn];
	node* nodes[maxn];
	int top=1;
	
	void adjust_down(int pos){
		while(pos>1 and *nodes[pos/2]>*nodes[pos]){
			swap(nodes[pos],nodes[pos/2]);
			id_to_pos[nodes[pos]->id]=pos;
			id_to_pos[nodes[pos/2]->id]=pos/2;
			pos=pos/2;
		}
	}
		
	void adjust_up(int pos){
		int compared;
		while(true){
			compared=pos*2;
			if(pos*2<top){
				if(pos*2+1<top)
					if(*nodes[pos*2+1]<*nodes[pos*2])
						compared=pos*2+1;
			}
			else break;
			
			if(*nodes[pos]>*nodes[compared]){
				swap(nodes[pos],nodes[compared]);
				id_to_pos[nodes[pos]->id]=pos;
				id_to_pos[nodes[compared]->id]=compared;
				pos=compared;
			}
			else break;
		}
	}

public:
	void push(node& a){
		nodes[top]=&a;
		id_to_pos[a.id]=top;
		top++;
		
		adjust_down(top-1);
	}
	
	node& front(){
		return *nodes[1];
	}
	
	void del(){
		//cout<<"id: "<<nodes[1]->id<<endl;
		nodes[1]=nodes[top-1];
		id_to_pos[nodes[1]->id]=1;
		top--;
		adjust_up(1);
	}
	
	void change(node& a,int value){
		if(a.value>value){
			a.value=value;
			if(id_to_pos[a.id]>=top)
				throw runtime_error("Changed deleted values");
				
			adjust_down(id_to_pos[a.id]);
		}
	}
	
	bool empty(){
		return top==1;
	}
};
