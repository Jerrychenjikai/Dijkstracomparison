#include <iostream>
#include <stdexcept>
#include "node.h"
#define maxn 2000005
#define maxc 1005
using namespace std;

struct heapnode{
	node* value=nullptr;
	
	heapnode* prev=nullptr;
	heapnode* nxt=nullptr;
	
	void remove(){//remove from linked list
		if(nxt==nullptr and prev==nullptr) throw runtime_error("item not in list");
		if(nxt!=nullptr)
			nxt->prev=prev;
		if(prev!=nullptr)
			prev->nxt=nxt;
		nxt=nullptr;
		prev=nullptr;
	}
	
	void add(heapnode* n){//connect behind n
		if(n==nullptr) throw runtime_error("invalid n");
		if(nxt!=nullptr or prev!=nullptr) throw runtime_error("item already in list");
		if(n->nxt!=nullptr)
			n->nxt->prev=this;
		nxt=n->nxt;
		prev=n;
		n->nxt=this;
	}
};

class priorityq{
private:
	heapnode buckets[maxc];
	int top=0;
	int last_deleted=0;
	
	int highestBit(uint32_t n) {
		if (n == 0) return 0;
		return 32 - __builtin_clz(n); // GCC/Clang
	}
		
	void break_up_bucket(){//find smallest bucket and break it up
		int current=1;
		while(buckets[current].nxt==nullptr) current++;
		
		heapnode* minn=nullptr;
		heapnode* cache=buckets[current].nxt;
		int min_value=2147483647;
		while(cache!=nullptr){
			if(cache->value->value<min_value){
				minn=cache;
				min_value=cache->value->value;
			}
			cache=cache->nxt;
		}
		last_deleted=min_value;
		
		cache=buckets[current].nxt;
		while(cache!=nullptr){
			cache->remove();
			push(*(cache->value),0);
			delete cache;
			cache=buckets[current].nxt;
		}
		return;
	}
	
	void debug_print() {
		cout << "Priority Queue State:" << endl;
		cout << "Top (number of elements): " << top << endl;
		cout << "Last Deleted Value: " << last_deleted << endl;
		cout << "Buckets:" << endl;
		
		for (int i = 0; i < maxc; i++) {
			bool first = true;
			heapnode* it = buckets[i].nxt;
			if (it != nullptr) {
				cout << "  Bucket[" << i << "]: ";
				while (it != nullptr) {
					if (!first) cout << " -> ";
					first = false;
					cout << "(id=" << it->value->id << ", value=" << it->value->value << ")";
					it = it->nxt;
				}
				cout << endl;
			}
		}
		cout << "End of Queue State\n" << endl;
	}
public:
	void init(){
		top=0;
		last_deleted=0;
		memset(buckets, 0, sizeof(buckets));
		
		return;
	}
	
	void push(node& a, bool actual=1){
		heapnode* cache=new heapnode;
		if(actual) top++;
		cache->value=&a;
		a.heaphandle=cache;
		
		int pos=highestBit(last_deleted^a.value);
		
		cache->add(&buckets[pos]);
		
	}
	
	node& front(){
		if(top==0) throw runtime_error("heap empty, no front element");
		if(buckets[0].nxt!=nullptr) return *(buckets[0].nxt->value);
		break_up_bucket();
		return *(buckets[0].nxt->value);
	}
	
	void del(){
		if(top==0) throw runtime_error("heap empty, no element to delete");
		
		if(buckets[0].nxt==nullptr) break_up_bucket();
		heapnode* cache=buckets[0].nxt;
		cache->remove();
		top--;
		delete cache;
	}
	
	void change(node& a, int value){
		if(value<=a.value){
			a.value=value;
			a.heaphandle->remove();
			delete a.heaphandle;
			push(a,0);
		}
	}
	
	bool empty(){
		return top==0;
	}
};