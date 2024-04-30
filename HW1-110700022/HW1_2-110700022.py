def isBipartite(adj,node):
    color_node = [-1]*(node+1)
    q = []
    for i in range(1,node+1):
        if color_node[i] == -1:
            q.append([i,0])
            color_node[i] = 0

            while len(q) != 0:
                p = q[0]
                q.pop(0)
                cur_node = p[0]
                color_cur_node = p[1]

                for j in adj[cur_node]:
                    if color_node[j] == color_cur_node:
                        return False
                    if color_node[j] == -1:
                        if color_cur_node == 1:
                            color_node[j] = 0
                        else:
                            color_node[j] = 1
                        q.append([j, color_node[j]])
    return True

def create_adjacency_list(node, edge):
    adjacency_list = [[] for _ in range(node+1)]

    for _ in range(edge):
        u, v = map(int, input().split())
        adjacency_list[u].append(v)
        adjacency_list[v].append(u)

    #
    return adjacency_list




node, edge = map(int, input().split())

adjacency_list = create_adjacency_list(node, edge)


if isBipartite(adjacency_list, node):
    print('Yes')
else:
    print('No')

