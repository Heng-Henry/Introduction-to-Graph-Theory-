#include<iostream>
#include<algorithm>
typedef long long ll;
using namespace std;
#define maxn 1000000
int r[maxn];
pair<ll, pair<int,int> > b[maxn];


struct weight_city{
	int name;
	ll weight;
};


bool cmp_weight(weight_city c1, weight_city c2)
{
	return c1.weight < c2.weight;
}

int parent(int node)
{
	while(r[node]!=node)
	{
		r[node] = r[r[node]];
		node = r[node];
	}
	return node;
}

void find(int vertex_1,int vertex_2)
{
	int parent_1 = parent(vertex_1);
	int parent_2 = parent(vertex_2);
	r[parent_1] = r[parent_2];
}




ll kruskal(int edge)
{
	int vertex_1 , vertex_2;
	long long cost, min_cost = 0;
	for(int i=0;i<edge;i++)
	{
		vertex_1 = b[i].second.first;
		vertex_2 = b[i].second.second;
		cost = b[i].first;
		if(parent(vertex_1)!=parent(vertex_2))
		{
			min_cost += cost;
			find(vertex_1,vertex_2);
		}
	}
	return min_cost;
}
int main()
{
	int query;
	cin >> query;
	while(query--)
	{
		int n,m;
		cin >> n >> m;
		weight_city city[n];
		int record_cityweight[n+1];
		for(int i=0;i<n;i++)
		{
			city[i].name = i+1;	// record the name of city by number
			cin >> city[i].weight;
			record_cityweight[i+1] = city[i].weight;
			r[i+1] = i+1;
		}
		sort(city,city+n,cmp_weight);
		weight_city min_city = city[0];
		
		int c = 0;
		for(int i=0;i<n;i++)
		{
			int min_name = min_city.name;
			if(min_name != (i+1))
			{
				long long cost = min_city.weight + record_cityweight[i+1];
				b[c] = make_pair(cost,make_pair(min_name,i+1));
				c++;
			}
			
		}
		for(int i=0;i<m;i++)
		{
			int u,v;
			ll w;
			cin >> u >> v >> w;
			b[c] = make_pair(w,make_pair(u,v));
			c++;
		}
		int num_edges = n-1+m;
		sort(b,b+num_edges);
		ll cost_minimum = kruskal(num_edges);
		cout << cost_minimum << endl;
		
		
	}
	
	
	
	
	
	return 0;
 } 
