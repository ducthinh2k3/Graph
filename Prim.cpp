#include <iostream>
#include <vector>
using namespace std;

struct Edge
{
    int u, v, w;
};

void printList(vector<vector<pair<int, int>>> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        for (int j = 0; j < list[i].size(); j++)
            cout << list[i][j].first << "-" << list[i][j].second << " ";
        cout << endl;
    }
}

vector<vector<pair<int, int>>> adjacencyList(int &vertices)
{
    int n, m;
    cin >> n >> m;
    vertices = n;
    vector<vector<pair<int, int>>> list(n);
    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        list[x].push_back({y, w});
        list[y].push_back({x, w});
    }
    return list;
}

void make_set(vector<bool> &used, int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        used.push_back(false);
    } // true: V(MST), false: V
}

void Prim(int u, vector<vector<pair<int, int>>> list, vector<bool> &used)
{
    used[u] = true;
    vector<Edge> MST;
    int d = 0;
    int vertices = list.size();
    while (MST.size() < vertices - 1)
    {
        int min_w = INT_MAX;
        int X, Y;
        for (int i = 0; i < vertices; i++)
        {
            if (used[i] == true)
            {
                for (pair<int, int> it : list[i])
                {
                    int j = it.first;
                    int trongso = it.second;
                    if (used[j] == false)
                    {
                        if (trongso < min_w)
                        {
                            min_w = trongso;
                            Y = i;
                            X = j;
                        }
                    }
                }
            }
        }
        MST.push_back({X,Y,min_w});
        d += min_w;
        used[X] = true;
    }
    cout << d << endl;
    for (Edge e : MST)
    {
        cout << e.u << " " << e.v << " " << e.w << endl;
    }
}

int main()
{
    int vertices = 0;
    vector<vector<pair<int, int>>> list = adjacencyList(vertices);
    //printList(list);
    cout << endl;
    vector<bool> used;
    make_set(used, vertices);
    Prim(0, list, used);
}