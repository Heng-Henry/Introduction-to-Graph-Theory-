#include <iostream>
#include <utility>
#include <queue>
#include <climits>
#include <vector>

using namespace std;

int N, M;

class FlowNetwork {
private:
    struct FlowEdge {
        int to, rev, flow, cap;
        FlowEdge(int t, int r, int f, int c): to(t), rev(r), flow(f), cap(c) {}
    };

    int nodes;
    vector<int> dist;
    vector<vector<FlowEdge>> graph;
    vector<bool> visited;

    int Augment(int u, int flow, int t, vector<int>& index) {
        if (u == t) return flow;

        for (; index[u] < (int)graph[u].size(); index[u]++) {
            FlowEdge &e = graph[u][index[u]];
            if (dist[e.to] == dist[u] + 1 && e.flow < e.cap) {
                int curFlow = min(flow, e.cap - e.flow);
                int tempFlow = Augment(e.to, curFlow, t, index);

                if (tempFlow > 0) {
                    e.flow += tempFlow;
                    graph[e.to][e.rev].flow -= tempFlow;
                    return tempFlow;
                }
            }
        }

        return 0;
    }

    bool BFS(int src, int des) {
        fill(dist.begin(), dist.end(), -1);
        dist[src] = 0;
        queue<int> q;
        q.push(src);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            for (auto &edge : graph[current]) {
                if (dist[edge.to] == -1 && edge.flow < edge.cap) {
                    dist[edge.to] = dist[current] + 1;
                    q.push(edge.to);
                }
            }
        }

        return dist[des] != -1;
    }

public:
    FlowNetwork(int n) {
        nodes = n;
        graph = vector<vector<FlowEdge>>(n);
        dist = vector<int>(n);
        visited = vector<bool>(n, false);
    }

    void AddEdge(int x, int y, int cap) {
        graph[x].push_back(FlowEdge(y, graph[y].size(), 0, cap));
        graph[y].push_back(FlowEdge(x, graph[x].size(), 0, 0));
    }

    int MaxFlow(int source, int sink) {
        for (int i = 0; i < nodes; i++) {
            for (FlowEdge &j : graph[i])
                j.flow = 0;
        }

        if (source == sink) return -1;

        int totalFlow = 0;
        while (BFS(source, sink)) {
            vector<int> index(nodes, 0);
            while (int flow = Augment(source, INT_MAX, sink, index))
                totalFlow += flow;
        }

        return totalFlow;
    }
};

int main() {
    cin >> N >> M;

    FlowNetwork flowNetwork(N * 2 + 1);
    
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;

        flowNetwork.AddEdge(v, u, 1);
        flowNetwork.AddEdge(u, v, 1);
    }

    int minFlow = INT_MAX;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i != j) 
                minFlow = min(minFlow, flowNetwork.MaxFlow(i, j));
        }
    }

    cout << minFlow << endl;

    return 0;
}
