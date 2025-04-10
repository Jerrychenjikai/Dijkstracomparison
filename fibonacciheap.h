#include <iostream>
#include <vector>
#include <cmath>
#include "node.h"
#define maxn 200005
using namespace std;

struct heapnode{
	node* value;
	bool mark=0;
	int degree=0;
	
	heapnode* prevbro=nullptr;
	heapnode* nxtbro=nullptr;
	
	heapnode* fa=nullptr;
	heapnode* firstchild=nullptr;
	
	heapnode* nxt=nullptr;
	heapnode* prev=nullptr;
};

class priorityq{
private:
	heapnode* id_to_root[maxn];
	
	heapnode* rootroot=nullptr; //root of root list
	heapnode* minn=nullptr;
	
	heapnode nodes[maxn];
	int top=0;
	
	void insert_into_rootlist(heapnode* a){
		heapnode* cacheroot = a;
		
		cacheroot->nxt=rootroot;
		if(rootroot!=nullptr) cacheroot->nxt->prev=cacheroot;
		rootroot=cacheroot;
	}
	
	void remove_from_rootlist(heapnode* a){
		if(a->nxt!=nullptr)
			a->nxt->prev=a->prev;
		if(a->prev!=nullptr)
			a->prev->nxt=a->nxt;
		else rootroot=a->nxt;
	}

public:
	void push(node& a){
		heapnode* cache = &nodes[top];//create a heapnode for a and attach a to it
		top++;
		cache->value=&a;
		id_to_root[a.id]=cache;
		
		insert_into_rootlist(cache);
		
		if(minn==nullptr or *(cache->value) < *(minn->value)) minn=cache;//update minn pointer
	}
	
	void change(node& a, int value){
		if(value>a.value){
			return;
		}
			//cout<<"cannot increase node size"<<endl;
		
		a.value=value;
		
		heapnode* cache = id_to_root[a.id];
		heapnode* cachefa;
		if(*(cache->value) < *(minn->value)) minn=cache;
		
		if(cache->fa!=nullptr and *(cache->fa->value)>a){
			do{
				cachefa=cache->fa;
				cache->fa=nullptr;
				
				if(cache->prevbro!=nullptr)
					cache->prevbro->nxtbro = cache->nxtbro;
				else
					cachefa->firstchild=cache->nxtbro;
				if(cache->nxtbro!=nullptr)
					cache->nxtbro->prevbro = cache->prevbro;
					
				insert_into_rootlist(cache);
				cache->mark=0;
				cache=cachefa;
				cachefa->degree--;
				
				if(!cache->mark){
					cache->mark=1;
					break;
				}
			}while(cache->fa!=nullptr);
		}
	}
	
	node& front(){
		return *(minn->value);
	}
	
	bool empty(){
		return (rootroot==nullptr);
	}
	
	void del(){
		remove_from_rootlist(minn);
		
		heapnode* cache=minn->firstchild;
		while(cache!=nullptr){
			cache->fa=nullptr;
			insert_into_rootlist(cache);
			cache=cache->nxtbro;
		}
		
		
		heapnode* unique_degree[maxn];
		
		const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
		double maxDegree = log(top) / log(phi);
		
		for(int i=0;i<maxDegree+5;i++) unique_degree[i]=nullptr;
		heapnode* rootcache=rootroot;
		heapnode* current;
		
		while(rootcache!=nullptr){
			current=rootcache;
			
			while(unique_degree[current->degree]!=nullptr){
				if(*(current->value) < *(unique_degree[current->degree]->value)){
					//remove larger from rootlist
					remove_from_rootlist(unique_degree[current->degree]);
					cache=unique_degree[current->degree];
					unique_degree[current->degree]=nullptr;
					
					//merge larger under smaller
					if(current->firstchild!=nullptr) current->firstchild->prevbro=cache;
					cache->prevbro=nullptr;
					cache->nxtbro=current->firstchild;
					current->firstchild=cache;
					current->degree++;
				}
				
				else{
					//remove larger from rootlist
					remove_from_rootlist(current);
					cache=unique_degree[current->degree];
					unique_degree[current->degree]=nullptr;
					
					//merge larger under smaller
					swap(current,cache);
					if(current->firstchild!=nullptr) current->firstchild->prevbro=cache;
					cache->prevbro=nullptr;
					cache->nxtbro=current->firstchild;
					current->firstchild=cache;
					current->degree++;
				}
			}
			rootcache=rootcache->nxt;
		}
		
		rootcache=rootroot;
		minn=nullptr;
		
		while(rootcache!=nullptr){
			if(minn==nullptr or *(minn->value)>*(rootcache->value)){
				minn=rootcache;
			}
			rootcache=rootcache->nxt;
		}
	}
};
			
