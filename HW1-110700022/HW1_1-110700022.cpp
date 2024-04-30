#include<iostream>
using namespace std;


int main()
{
	int matrix[1001][1001] = {0};
	int in_deg[1001] = {0};
	int out_deg[1001] = {0};
	int n,m;
	cin >> n >> m;
	for(int i=0;i<m;i++)
	{
		int source,destination,weight;
		cin >> source >> destination >> weight;
		matrix[source][destination] = weight;
		in_deg[destination] += 1;
		out_deg[source] += 1;
	}
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cout << matrix[i][j] << " ";
		} 
		cout << endl;
	}
	
	for(int i=1;i<=n;i++)
	{
		 cout << in_deg[i] << " " << out_deg[i] << endl;
	}
	
	
	return 0;
 } 
