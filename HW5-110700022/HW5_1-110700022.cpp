#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

bool containsK33(int vertices, bool connection[18][18], int degree[18])
{
    vector<int> is_end;

    for (int i = 1; i <= vertices; i++)
    {
        if (degree[i] == 3)
            is_end.push_back(i);
    }

    if (is_end.size() != 6)
        return false;

    while (true)
    {
        bool flag = true;

        for (int i = 1; i <= vertices; i++)
        {
            if (degree[i] == 2)
            {
                flag = false;
                degree[i] = 0;
                int a = -1, b;

                for (int j = 1; j <= vertices; j++)
                {
                    if (connection[i][j])
                    {
                        if (a == -1)
                            a = j;
                        else
                            b = j;
                    }
                }

                connection[i][b] = false;
                connection[i][a] = false;
                connection[a][i] = false;
                connection[b][i] = false;
                connection[a][b] = true;
                connection[b][a] = true;
            }
        }

        if (flag)
            break;
    }

    vector<int> is_down;
    vector<int> is_up;
    is_up.push_back(is_end[0]);

    for (int i = 1; i <= 5; i++)
    {
        if (connection[is_end[0]][is_end[i]])
            is_down.push_back(is_end[i]);
        else
            is_up.push_back(is_end[i]);
    }

    if (is_up.size() != 3 || is_down.size() != 3)
        return false;

    int temp = 0;

    for (int i : is_up)
    {
        for (int j : is_down)
        {
            if (connection[i][j])
                temp++;
        }
    }

    return (temp == 9);
}

bool containsK5(int vertices, bool connection[18][18], int degree[18])
{
    vector<int> is_end;

    for (int i = 1; i <= vertices; i++)
    {
        if (degree[i] == 4)
            is_end.push_back(i);
    }

    if (is_end.size() != 5)
        return false;

    while (true)
    {
        bool flag = true;

        for (int i = 1; i <= vertices; i++)
        {
            if (degree[i] == 2)
            {
                flag = false;
                degree[i] = 0;
                int a = -1, b;

                for (int j = 1; j <= vertices; j++)
                {
                    if (connection[i][j])
                    {
                        if (a == -1)
                            a = j;
                        else
                            b = j;
                    }
                }

                connection[i][b] = false;
                connection[i][a] = false;
                connection[a][i] = false;
                connection[b][i] = false;
                connection[a][b] = true;
                connection[b][a] = true;
            }
        }

        if (flag)
            break;
    }

    int temp = 0;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (connection[is_end[i]][is_end[j]])
            {
                temp++;
            }
        }
    }

    return (temp == 20);
}

int main()
{
    
    int testCases;
    cin >> testCases;

    while (testCases--)
    {
        int vertices, edges;
        cin >> vertices >> edges;

        bool connection[18][18];
        memset(connection, false, sizeof(connection));

        int degree[18];
        memset(degree, 0, sizeof(degree));

        vector<pair<int, int>> edgeList(edges);

        for (int i = 0; i < edges; i++)
        {
           
            cin >> edgeList[i].first >> edgeList[i].second;
            connection[edgeList[i].first][edgeList[i].second] = true;
            connection[edgeList[i].second][edgeList[i].first] = true;
            degree[edgeList[i].first]++;
            degree[edgeList[i].second]++;
        }

        bool ans = true;

        for (int i = 1; i < (1 << edges); i++)
        {
            memset(connection, false, sizeof(connection));
            memset(degree, 0, sizeof(degree));

            for (int j = 0; j < edges; j++)
            {
                if ((i >> j) & 1)
                {
                    int a = edgeList[j].first;
                    int b = edgeList[j].second;
                    connection[a][b] = true;
                    degree[a]++;
                    connection[b][a] = true;
                    degree[b]++;
                }
            }

            if (containsK5(vertices, connection, degree) || containsK33(vertices, connection, degree))
            {
                cout << "No\n";
                ans = false;
                break;
            }
        }

        if (ans)
            cout << "Yes\n";
    }

    return 0;
}
