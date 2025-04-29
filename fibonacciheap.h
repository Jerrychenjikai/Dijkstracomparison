#include <iostream>
#include <vector>
#include <cmath>
#include "node.h"
#define maxn 2000005
using namespace std;

struct heapnode{
	node* value;
	bool mark=0;
	int degree=0;
	
	heapnode* fa=nullptr;
	heapnode* firstchild=nullptr;
	
	heapnode* nxt=nullptr;
	heapnode* prev=nullptr;
};

class priorityq{
private:	
	heapnode* rootroot=nullptr; //root of root list
	heapnode* minn=nullptr;
	heapnode* rootend=nullptr;
	
	int top=0;
	
	void insert_into_rootlist(heapnode* a){
		heapnode* cacheroot = a;
		cacheroot->prev=nullptr;
		cacheroot->nxt=nullptr;
		
		cacheroot->nxt=rootroot;
		cacheroot->prev=nullptr;
		if(rootroot!=nullptr) rootroot->prev=cacheroot;
		else rootend=cacheroot;
		rootroot=cacheroot;
	}
	
	void remove_from_rootlist(heapnode* a){
		if(a->nxt!=nullptr)
			a->nxt->prev=a->prev;
		else rootend=a->prev;
		if(a->prev!=nullptr)
			a->prev->nxt=a->nxt;
		else rootroot=a->nxt;
		a->nxt=nullptr;
		a->prev=nullptr;
	}

public:
	void push(node& a){
		heapnode* cache = new heapnode;//create a heapnode for a and attach a to it
		top++;
		cache->value=&a;
		a.heaphandle = cache;
		
		insert_into_rootlist(cache);
		
		if(minn==nullptr or *(cache->value) < *(minn->value)) minn=cache;//update minn pointer
	}
	
	void change(node& a, int value){
		if(value>a.value){
			return;
		}
				
		a.value=value;
					
		heapnode* cache = a.heaphandle;
		heapnode* cachefa;
		if(*(cache->value) < *(minn->value)){
			minn=cache;
		}
						
		if(cache->fa!=nullptr and *(cache->fa->value)>a){
			do{
				cachefa=cache->fa;
				cache->fa=nullptr;
				
				if(cache->prev!=nullptr)
					cache->prev->nxt = cache->nxt;
				else
					cachefa->firstchild=cache->nxt;
				if(cache->nxt!=nullptr)
					cache->nxt->prev = cache->prev;
					
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
		top--;
		
		
		heapnode* cache=minn->firstchild;
		heapnode* cachenxt=nullptr;
		while(cache!=nullptr){
			cache->fa=nullptr;
			cachenxt=cache->nxt;
			insert_into_rootlist(cache);
			cache=cachenxt;
		}
		
		
		heapnode* unique_degree[maxn/10];
		
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
					cache=unique_degree[current->degree];
					
					remove_from_rootlist(cache);
					unique_degree[current->degree]=nullptr;
					
					//merge cache under current
					//cout<<"1merged: "<<cache->value->id<<"under: "<<current->value->id<<endl;
					if(current->firstchild!=nullptr) current->firstchild->prev=cache;
					cache->prev=nullptr;
					cache->nxt=current->firstchild;
					current->firstchild=cache;
					cache->fa=current;
					current->degree++;
				}
				
				else{
					//remove larger from rootlist
					
					cache=unique_degree[current->degree];
					remove_from_rootlist(cache);
					unique_degree[current->degree]=nullptr;
					
					//merge larger under smaller
					//take out cache and insert it beside current
					cache->prev=current->prev;
					cache->nxt=current->nxt;
					if(current->nxt!=nullptr) current->nxt->prev=cache;
					else rootend=cache;
					if(current->prev!=nullptr) current->prev->nxt=cache;
					else rootroot=cache;
					rootcache=cache;
					
					//merge current under cache
					if(cache->firstchild!=nullptr) cache->firstchild->prev=current;
					current->nxt=cache->firstchild;
					current->prev=nullptr;
					cache->firstchild=current;
					current->fa=cache;
										
					cache->degree++;
					current=cache;
				}
			}
			unique_degree[current->degree]=current;
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
			
