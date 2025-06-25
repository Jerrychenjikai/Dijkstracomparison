#include <iostream>
#include "node.h"
#include "binaryheap.h"//could be changed to other queues
#include <vector>
#include <cstdio>
#include <chrono>
#define maxn 2000005
using namespace std;

/*
Functions required for the priority queue:
1. void push(node& a)
2. void change(node& a, int value) (change the value of a node)
3. void del() (delete the smallest node)
4. node& front() (node with smallest value)
5. bool empty() return true if no element in queue
6. void init() clear the queue for next iteration
*/

int n,m;//number of nodes/sides
//ensure: nodes are labelled with consecutive id starting from 1
int root;

node nodes[maxn];

node* current;

int start,endd,cost;

double avg_time=0;
double max_time=0;
double min_time=10000;

priorityq q;

int main()
{
	freopen("100000.in","r",stdin);
	scanf("%d %d %d",&n, &m, &root);
	
	for(int i=0;i<=n;i++) nodes[i].id=i;
	
	for(int i=0;i<m;i++){
		scanf("%d %d %d",&start, &endd, &cost);
		
		//establish graph structure
		nodes[start].sides.push_back(endd);
		nodes[start].cost.push_back(cost);
	}
	
	for(int i1=0;i1<100;i1++){
		q.init();
		
		//start timer
		auto start_time = chrono::high_resolution_clock::now();
		
		//push all nodes into the queue because they are initially all unreached
		for(int i=1;i<=n;i++) q.push(nodes[i]);
		
		//root node has 0 distance from itself
		q.change(nodes[root],0);
			
		while(!q.empty()){
			current=&q.front(); //obtain the smallest unreached node
			q.del(); //remove this node (because it is now reached)
			if(current->value==2147483647) continue; 
			for(int i=0;i<current->sides.size();i++){
				//relax all the edges (The compare action is done in this function)
				q.change(nodes[current->sides[i]], current->value+current->cost[i]);
			}
		}
		
		//end timer
		auto end_time = chrono::high_resolution_clock::now();
	    chrono::duration<double> elapsed = end_time - start_time;
			
		for(int i=1;i<=10;i++) printf("%d ",nodes[i].value);	
		
		printf("\n\nexecution time: %f seconds\n", elapsed.count());
		avg_time+=elapsed.count();
		max_time=max(max_time, elapsed.count());
		min_time=min(min_time, elapsed.count());
	}
	
	printf("\n\naverage execution time: %f seconds\n", avg_time/100);
	printf("\nmax execution time: %f seconds\n", max_time);
	printf("\nmin execution time: %f seconds\n", min_time);
	
	return 0;
}
			
