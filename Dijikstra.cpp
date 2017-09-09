#include <stdio.h>
#include<queue>
#include <time.h>
#include<iostream>
#include<limits.h>
#include<bits/stdc++.h>
int graph[3005][3005],d[3000];
using namespace std;
struct thing
{
	int dist;
	int vertex;
	bool operator<(const thing &o) const
	{
		return dist>o.dist;
	}
};
float dijkstra(int n,int s)
{		 	
	thing T[3000];
	priority_queue<thing> pq;		
	T[s].dist = 0;
	T[s].vertex=s;
	d[s]=0;
	for (int i = 0; i < n; i++)
	{   	if(i==s) continue;
		T[i].dist = INT_MAX;
		T[i].vertex = i;
		d[i]=INT_MAX;
	}
	for(int i=0;i<n;i++)
	{
		pq.push(T[i]);
	}
	clock_t t1,t2;
	t1=clock();
	while(!pq.empty())
	{
		struct thing t=pq.top(); pq.pop();
		for(int j=0;j<n;j++)
		{
			if(graph[t.vertex][j]!=0)
			{
				if((d[t.vertex] + graph[t.vertex][j] < d[j]))
				{	
					d[j] = d[t.vertex]+graph[t.vertex][j];
					struct thing t4;
					t4.dist=d[j];
					t4.vertex=j;
					pq.push(t4);
				}
			}
		}			
	}
	t2=clock();
	float diff ((float)t2-(float)t1);
	float seconds = diff*0.00247875217;
	return seconds;
	
}
int main()
{
		int n,s,x;
		scanf("%d %d",&n,&s);
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{	scanf("%d ",&x);
				graph[i][j]=x;
			}
			if(i==n-2) break;
		}
		float diff;
		diff=dijkstra(n,s-1);
		printf("%f\n",diff);
		
		printf("Shortest Distance from Source:(%d) to all vertices\n",s);
		for(int i=0;i<n;i++)
		{ if(i==s-1) printf("0 ");
            		else if(d[i]== INT_MAX || d[i]<0)
                    		printf("-1 ");
			else printf("%d ",d[i]);
		}
		printf("\n");
	
	return 0;
}


