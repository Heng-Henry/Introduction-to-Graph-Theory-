#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100005

int n, m;
int total = 0;
int num = 0, cut_set_size = 0, root;
int discovery_time[MAXN], lower[MAXN];
int first[MAXN * 2], to_node[MAXN * 2], next_edge[MAXN * 2];
vector<vector<int>> adj_list;
bool is_cut_vertex[MAXN];

void dfs(int current_node) {
    int child_count = 0;
    num++;
    discovery_time[current_node] = num;
    lower[current_node] = num;
    for (int i = first[current_node]; i; i = next_edge[i]) {
        int neighbor = to_node[i];
        if (!discovery_time[neighbor]) {
            dfs(neighbor);
            if (lower[neighbor] < lower[current_node]) {
                lower[current_node] = lower[neighbor];
            }
            if (lower[neighbor] >= discovery_time[current_node]) {
                child_count++;
                if (current_node != root || child_count >= 2) {
                    is_cut_vertex[current_node] = true;
                }
            }
        } else if (discovery_time[neighbor] < lower[current_node]) {
            lower[current_node] = discovery_time[neighbor];
        }
    }
}

void add_edge(int node1, int node2) {
    next_edge[++total] = first[node1];
    first[node1] = total;
    to_node[total] = node2;
}

void print_result() {
    for (int i = 1; i <= n; i++)
        if (is_cut_vertex[i]) cut_set_size++;
    cout << cut_set_size << endl;
    for (int i = 1; i <= n; i++)
        if (is_cut_vertex[i]) cout << i << " ";
}

int main() {
    cin >> n >> m;
    adj_list.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        add_edge(node1, node2);
        add_edge(node2, node1);
    }

    for (int i = 1; i <= n; i++) {
        if (!discovery_time[i]) {
            root = i;
            dfs(i);
        }
    }
    print_result();
}
