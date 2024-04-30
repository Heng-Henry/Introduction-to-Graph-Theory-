#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3f;
void Dijkstra(vector<vector<pair<long long,long long>>> &adj_list,vector<int>& pre,vector<long long>& dis,int s,int n)
{
    // the weight and node
    priority_queue<pair<long long, long long>,vector<pair<long long,long long>>,greater<pair<long long,long long>> > q;
    
    for(int i=1;i<=n;i++) q.push({INF, i});

    dis[s] = 0;   // source
    pre[s] = s;
    while(!q.empty())
    {
        pair<int,int> e = q.top();
        q.pop();
        long long ver = e.second;
        for(auto i:adj_list[ver])
        {
            long long weight = i.first;
            long long vertex = i.second;

            long long new_weight = dis[ver]+ weight;
            if(new_weight < dis[vertex] || (new_weight == dis[vertex] && pre[vertex] > ver))  // shortest path
            {
                dis[vertex] = new_weight; // update the weight
                pre[vertex] = ver;    // update the previous vertex
                q.push({new_weight, vertex});
            }
        }
    }

}
int main()
{

    int  x,y;
    cin >> x >> y;
    while(x--)
{
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> p1(n+1,-1);
    vector<int> pn(n+1,-1);

    vector<vector<pair<long long,long long>>> adj_list(n+1);
    vector<long long > dis1(n+1,INF);
    vector<long long> disn(n+1,INF);
    

    // input 
    long long a,b,c;
    for(int i=0;i<m;i++)
    {
        cin >> a >> b >> c;
        adj_list[b].push_back({c,a});
    }
    // find shortest path
    Dijkstra(adj_list,p1,dis1,1,n);
    Dijkstra(adj_list,pn,disn,n,n);

    // hold the case of k=1
    if(k==1)
    {
        for(int i=1;i<=n;i++)
        {
            
            if(dis1[i]==INF) cout << -1;
            
            else cout << dis1[i];
            

            if(i==n) cout << endl;
            
            else cout << " ";
            
            
        }
    }
    
    else
    {
        vector<long long> dnn(n+2,INF);
        vector<int> t(n+2,-1);

        adj_list.push_back(vector<pair<long long,long long>>(0));

        for(int i=1;i<=n;i++) adj_list[n+1].push_back({dis1[i]+disn[i],i});

        Dijkstra(adj_list,t,dnn,n+1,n+1);
        //
        for(int i=1;i<=n;i++)
        {
            
            if(dis1[i]==INF || disn[i]==INF) cout << -1;
            else cout << dnn[i];

            //
            if(i==n) cout << endl;
            else  cout << " ";
            
        }
        
    }

}

    return 0;
}