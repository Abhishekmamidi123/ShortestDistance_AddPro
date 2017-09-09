#include<stdio.h>
#include<iostream>
#include<stack>
#include<queue>
#define INTMAX 10000
using namespace std;
struct node
{
	int degree;
	int vertex;
	bool operator<(const node &o) const
	{
		return degree>o.degree;
	}
};
class ShortestPath{
	public:
		int **Graph,**Weight,**UpdatedNeighbours,N,*RemovedNodes,*distance,source,*degree;
		priority_queue<node> Q;
		stack<int> S;
		void scan();
		void scanInitialise();
		void UpdateNeighbours(int vertex);
		void UpdateWeights(int);
		void topToBottom();
		void bottomToTop();
		void Initialize(int,int);
		void PrintShortestDistances();
		ShortestPath(){	
		}
};
void ShortestPath::Initialize(int x,int y)
{
	N=x;
	source=y;
	Graph=new int*[N];
	Weight=new int*[N];
}
void ShortestPath::PrintShortestDistances()
{
	printf("Shortest Distance from Source:(%d) to all vertices\n",source+1);
	for(int i=0;i<N;i++)
		cout<<distance[i]<<" ";
	cout<<"\n";
}
void ShortestPath::scanInitialise()
{
	// Scanning weights in the form of a matrix and updating degrees of all nodes in "degreeCount" array.
	degree=new int[N];
	for(int i=0;i<N;i++)
	{	int degreeCount=0;	
		Weight[i]=new int[N];
		for(int j=0;j<N;j++)
		{
			cin>>Weight[i][j];
			if(Weight[i][j]>0) degreeCount++;
			else{
				Weight[i][j]=INTMAX;
			}			
		}
		degree[i]=degreeCount;
	}
	// Mintaining an adjacency list "Graph" based on "Weight" 2D array and pushing degrees of all nodes in the priorityqueue "Q".
	for(int i=0;i<N;i++)
	{	int k=0;
		Graph[i]=new int[degree[i]];
		for(int j=0;j<N;j++)
		{
			if(Weight[i][j]!=INTMAX) {
				Graph[i][k]=j;
				k++;
			}
		}
		
		struct node p;
		p.vertex=i;
		p.degree=degree[i];
		Q.push(p);
	}
	
	// Creating an array to store neighbours when we are removing nodes.
	UpdatedNeighbours = new int*[N];
	// Keep track of removed nodes. 0-Not removed, 1-removed.
	RemovedNodes = new int[N];
	for(int i=0;i<N;i++){
		RemovedNodes[i] = 0;
	}
}
void ShortestPath :: UpdateNeighbours(int vertex){     // This function is called everytime we remove a node.
	// UpdatedNeighbours (adjacency list)  --> stores the neighbours that are present currently at the time of removing the node.  This adjacency list is used in topToBottom approach.
	UpdatedNeighbours[vertex] = new int[degree[vertex]];
	for(int i=0;i<degree[vertex];i++){
		if(RemovedNodes[Graph[vertex][i]] == 0){
			UpdatedNeighbours[vertex][i] = Graph[vertex][i];
		}
	}
}

void ShortestPath :: UpdateWeights(int vertex){       // This function is called everytime we removed a node.
	int i,j,x,y;
	// Here we are updating the weights after removing a node and the degrees of it's neighbours.
	for(i=0;i<degree[vertex];i++){
		degree[UpdatedNeighbours[vertex][i]] = degree[UpdatedNeighbours[vertex][i]] - 1;
	}
	for(i=0;i<degree[vertex]-1;i++){
		for(j=i+1;j<degree[vertex];j++){
			x=UpdatedNeighbours[vertex][i];
			y=UpdatedNeighbours[vertex][j];
			if(Weight[x][y] > Weight[x][vertex] + Weight[y][vertex]){
				if(Weight[x][y] != INTMAX){  
					Weight[x][y] = Weight[x][vertex] + Weight[y][vertex];
					Weight[y][x] = Weight[x][y];
				}
				else{
					Weight[x][y] = Weight[x][vertex] + Weight[y][vertex];
					Weight[y][x] = Weight[x][y];
					degree[x] = degree[x] + 1;
					degree[y] = degree[y] + 1;
				}		
			}
		}
	}
	// After updating the degrees of it's neighbours we again push the duplicate nodes into the priority queue.s
	for(i=0;i<degree[vertex];i++){
		struct node p;
		p.vertex=Graph[vertex][i];
		p.degree=degree[Graph[vertex][i]];
		Q.push(p);
	}
}
void ShortestPath :: bottomToTop(){
	struct node p,q;
	bool visited[N];
	int i;
	for(i=0;i<N;i++){
		visited[i] = false;
	}
	int u,count = 0,flag1=0;
	p = Q.top();	
	u = p.vertex;
	Q.pop();
	RemovedNodes[u]=1;
	// Here we are removing the nodes from the queue till we remain with 4 nodes in the queue.
	while(count < N-4){
		if(u==source)
		{	q.vertex=p.vertex;
			q.degree=p.degree;
			flag1=1;
		}
		else{
			if(visited[u] == false){
				visited[u] = true;
				S.push(u);
				count++;
				UpdateNeighbours(u);  // Useful in TopToBottom Aproach.
				UpdateWeights(u);      // Removing node u and updating distances and degree of node u's neighbours.
			}
		}
		p = Q.top();	
		u = p.vertex;
		Q.pop();
	}
	Q.push(p);
	if(flag1==1){
		Q.push(q);
	}
	for(int i=0;i<N;i++) distance[i]=0;
	int temp[3];
	bool vis[3];
	i=0;
	// As priority queue contains the remaining three nodes and their duplicates.So, instead of removing the top three we will pop until all the remaining three are stored in temp array.
	while(Q.size()>0)
	{	
		p = Q.top();
		Q.pop();	
		u = p.vertex;
		int flag = 0;
		for(int y=0;y<i;y++)
		{
			if(temp[y]==u){
				flag = 1;
				break;
			}
		}
		if(u!=source && flag == 0)
		{	temp[i]=u;
			i++;
		}
	}
	// Finding shortestdistance from source to remaining 3 nodes.
	for(int k=0;k<2;k++){
		for(i=0;i<3;i++)
		{	int min=Weight[source][temp[i]];	
			for(int j=0;j<3;j++)
			{
				if(i!=j){					
					if(Weight[source][temp[j]]+Weight[temp[i]][temp[j]] < min)
						min=Weight[source][temp[j]]+Weight[temp[i]][temp[j]];
				}
			}
			distance[temp[i]]=min;
			Weight[source][temp[i]] = min;
		}
	}
}
void ShortestPath :: topToBottom(){
	int k;
	// Removing nodes from the stack and finding shortest distance from source using its updated neighbour's shortest distance.
	while(S.size()>0){
		k = S.top();
		int min = distance[UpdatedNeighbours[k][0]]+Weight[k][UpdatedNeighbours[k][0]];
		for(int i=1 ; i<degree[k] ; i++){
			if(distance[UpdatedNeighbours[k][i]]+Weight[k][UpdatedNeighbours[k][i]] < min){
				min = distance[UpdatedNeighbours[k][i]]+Weight[k][UpdatedNeighbours[k][i]];
			}
		}
		distance[k] = min;
		S.pop();
	}
}
int main()
{
	int source,n;
	scanf("%d %d",&source,&n);
	ShortestPath SP;
	SP.Initialize(n,source-1);
	SP.scanInitialise();
	SP.bottomToTop();
	SP.topToBottom();
	SP.PrintShortestDistances();
}
