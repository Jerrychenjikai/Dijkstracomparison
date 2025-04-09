#include <iostream>
#include <vector>
#include "node.h"
#define maxn 200005
using namespace std;

struct rootnode;

struct heapnode{
	node* value;
	bool mark=0;
	int degree=0;
	
	heapnode* prevbro=nullptr;
	heapnode* nxtbro=nullptr;
	
	heapnode* fa=nullptr;
	heapnode* firstchild=nullptr;
	
	rootnode* root=nullptr;
};

struct rootnode{
	heapnode* value;
	rootnode* prev=nullptr;
	rootnode* nxt=nullptr;
};

class priorityq{
private:
	heapnode* id_to_root[maxn];
	
	rootnode* rootroot=nullptr; //root of root list
	heapnode* minn=nullptr;
	
	heapnode nodes[maxn];
	int top=0;
	
	void insert_into_rootlist(heapnode* a){
		rootnode* cacheroot = new rootnode();
		cacheroot->value = a;
		a->root = cacheroot;
		
		cacheroot->nxt=rootroot;
		if(rootroot!=nullptr) cacheroot->nxt->prev=cacheroot;
		rootroot=cacheroot;
	}
	
	void remove_from_rootlist(rootnode* a){
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
		remove_from_rootlist(minn->root);
		
		heapnode* cache=minn->firstchild;
		while(cache!=nullptr){
			cache->fa=nullptr;
			insert_into_rootlist(cache);
			cache=cache->nxtbro;
		}
		
		
		rootnode* unique_degree[maxn];
		for(int i=0;i<maxn;i++) unique_degree[i]=nullptr;
		rootnode* rootcache=rootroot;
		rootnode* current;
		
		while(rootcache!=nullptr){
			current=rootcache;
			
			while(unique_degree[current->value->degree]!=nullptr){
				if(*(current->value->value) < *(unique_degree[current->value->degree]->value->value)){
					//remove larger from rootlist
					remove_from_rootlist(unique_degree[current->value->degree]);
					cache=unique_degree[current->value->degree]->value;
					unique_degree[current->value->degree]=nullptr;
					
					//merge larger under smaller
					cache->fa=current->value;
					if(current->value->firstchild!=nullptr) current->value->firstchild->prevbro=cache;
					cache->prevbro=nullptr;
					cache->nxtbro=current->value->firstchild;
					current->value->firstchild=cache;
					current->value->degree++;
				}
				
				else{
					//remove larger from rootlist
					remove_from_rootlist(current);
					cache=unique_degree[current->value->degree]->value;
					unique_degree[current->value->degree]=nullptr;
					
					//merge larger under smaller
					swap(current->value,cache);
					current->value->root=current;
					cache->fa=current->value;
					if(current->value->firstchild!=nullptr) current->value->firstchild->prevbro=cache;
					cache->prevbro=nullptr;
					cache->nxtbro=current->value->firstchild;
					current->value->firstchild=cache;
					current->value->degree++;
				}
			}
			rootcache=rootcache->nxt;
		}
		
		rootcache=rootroot;
		minn=nullptr;
		
		while(rootcache!=nullptr){
			if(minn==nullptr or *(minn->value)>*(rootcache->value->value)){
				minn=rootcache->value;
			}
			rootcache=rootcache->nxt;
		}
	}
};
			