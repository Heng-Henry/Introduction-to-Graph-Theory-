#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int to, capa, re;
    Edge(int to_in, int capa_in, int re_in) : to(to_in), capa(capa_in), re(re_in) {}
};

vector<vector<Edge>> graph(6000);
vector<bool> visited(6000, false);

void addEdgeToGraph(int temp1, int temp2, int capacity) {
    graph[temp1].push_back(Edge(temp2, capacity, graph[temp2].size()));
    graph[temp2].push_back(Edge(temp1, 0, graph[temp1].size() - 1));
}

int DFS(int curNode, int target, int flow) {
    if (curNode == target) return flow;

    visited[curNode] = true;
    int curSize = graph[curNode].size();

    for (int i = 0; i < curSize; ++i) {
        Edge& edge = graph[curNode][i];

        if (!visited[edge.to] && edge.capa > 0) {
            int currentFlow = DFS(edge.to, target, min(flow, edge.capa));

            if (currentFlow > 0) {
                edge.capa -= currentFlow;
                graph[edge.to][edge.re].capa += currentFlow;
                return currentFlow;
            }
        }
    }

    return 0;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i) {
        int num;
        cin >> num;

        for (int j = 0; j < num; ++j) {
            int temp;
            cin >> temp;
            addEdgeToGraph(1000 + i, 2000 + temp, 1);
        }
    }

    addEdgeToGraph(0, 1, n + k);

    for (int i = 1; i <= n; ++i) {
        addEdgeToGraph(1, 1000 + i, 2);
    }

    for (int i = 1; i <= m; ++i) {
        addEdgeToGraph(2000 + i, 5000, 1);
    }

    int count = 0;
    while (true) {
        for (int i = 0, length = visited.size(); i < length; ++i) visited[i] = false;
        int flow = DFS(0, 5000, INT_MAX);

        if (flow == 0) {
            cout << count << endl;
            return 0;
        }

        count += flow;
    }
}
