#include<iostream>
#include<queue>
#include<vector>
#define maxn 100002
using namespace std;


bool visited[maxn];
queue<int>q;
int hei = 0;
vector<vector<int>>adj_list(maxn);


// use this 2d vector to store the height and parent
vector<vector<int>>output(maxn,vector<int>({-1,0}));


void build_tree(int parent,int pivot)
{
    visited[pivot] = true;
    output[pivot][1] = parent;
    bool f = true;
    for(int i=0,len=adj_list[pivot].size();i<len;i++)
    {
        if(!visited[adj_list[pivot][i]])
        {
            build_tree(pivot,adj_list[pivot][i]);
            f = false;
        }
    }
    if(f) q.push(pivot);
}
void height_calculate()
{
    while(q.size())
    {
      int n = q.front();
      int hei = 0;
      while(true)
      {
        // iteratively update the height and previous nodes
        if(n==-1) break;    // root
        if(output[n][0]>=hei) break;    
        else
        {
            output[n][0] = hei;
        }
        n = output[n][1];
        hei++;
      }
      q.pop();
    }

}







int main()
{
    int n;
    cin >> n;

    int temp1,temp2;
	for(int i=0;i<n-1;i++)
	{
		
		cin >> temp1 >> temp2;
		adj_list[temp1].push_back(temp2);
		adj_list[temp2].push_back(temp1);
		
	}
    build_tree(-1,1);
    height_calculate();
    for(int i=1;i<=n;i++) cout << output[i][0] << " " << output[i][1] << endl;


    return 0;
}