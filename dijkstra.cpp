#include <iostream>
#include "node.h"
#include "radixheap.h"
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
*/

int n,m;//number of nodes/sides
//ensure: nodes are labelled with consecutive id starting from 1
int root;

node nodes[maxn];

node* current;

int start,endd,cost;

priorityq q;

int main()
{
	freopen("1e6 sides/10e5.in","r",stdin);
	scanf("%d %d %d",&n, &m, &root);
	
	for(int i=0;i<=n;i++) nodes[i].id=i;
	
	for(int i=0;i<m;i++){
		scanf("%d %d %d",&start, &endd, &cost);
		nodes[start].sides.push_back(endd);
		nodes[start].cost.push_back(cost);
	}
	
	//start timer
	auto start_time = chrono::high_resolution_clock::now();
	
	for(int i=1;i<=n;i++) q.push(nodes[i]);
		
	q.change(nodes[root],0);
		
	while(!q.empty()){
		current=&q.front();
		q.del();
		if(current->value==2147483647) continue;
		for(int i=0;i<current->sides.size();i++){
			q.change(nodes[current->sides[i]], current->value+current->cost[i]);
		}
	}
	
	//end timer
	auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;
		
	for(int i=1;i<=n;i++) printf("%d ",nodes[i].value);	
	
	printf("\n\nexecution time: %f seconds\n", elapsed.count());
	
	return 0;
}
			
