#include <iostream>
#include <vector>
using namespace std;

struct Edge
{
    int u;
    int v;
    int w;
};

void make_set(vector<int> &parent, vector<int> &size, int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        parent.push_back(i);
        size.push_back(1);
    }
}

int find(int v, vector<int> &parent) // tim parent
{
    if (v == parent[v])
        return v;
    return parent[v] = find(parent[v], parent);
}

bool Union(int a, int b, vector<int> &parent)
{
    a = find(a, parent);
    b = find(b, parent);
    if (a != b)
    {
        parent[b] = a;
        return true;
    }
    return false;
}

void printList(vector<vector<int>> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        for (int j = 0; j < list[i].size(); j++)
            cout << list[i][j] << " ";
        cout << endl;
    }
}

vector<vector<int>> adjacencyList(int &vertices)
{
    int n = 0;
    int m = 0;
    cin >> n >> m;
    vertices = n;
    vector<vector<int>> list(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        list[x].push_back(y);
        list[y].push_back(x);
    }
    return list;
}

vector<Edge> listEdge(int &vertices)
{
    int n = 0;
    int m = 0;
    cin >> n >> m;
    vector<Edge> listEdge;
    vertices = n;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        Edge e;
        e.u = u;
        e.v = v;
        e.w = w;
        listEdge.push_back(e);
    }
    return listEdge;
}

void swapEdge(Edge &a, Edge &b)
{
    Edge temp = a;
    a=b;
    b= temp;
}

// sort listEdge
void sort(vector<Edge> &listEdge)
{
    for (int i = 0; i < listEdge.size() - 1; i++)
    {
        int index = i;
        for (int j = i + 1; j < listEdge.size(); j++)
        {
            if (listEdge[j].w < listEdge[index].w)
                index = j;
        }
        swapEdge(listEdge[i], listEdge[index]);
    }
}

void Kruskal(vector<Edge> listEdge, int vertices, vector<int> &parent)
{
    vector<Edge> MST;
    sort(listEdge);
    int d = 0;
    for (int i = 0; i < listEdge.size(); i++)
    {
        if (MST.size() == vertices - 1)
            break;
        Edge e = listEdge[i];
        if (Union(e.u, e.v, parent))
        {
            MST.push_back(e);
            d += e.w;
        }
    }

    if (MST.size() != vertices - 1)
        cout << "Do thi khong lien thong" << endl;
    else
    {
        cout << "Trong so: " << d << endl;
        for (int j = 0; j < MST.size(); j++)
        {
            cout << MST[j].u << " " << MST[j].v << " " << MST[j].w << endl;
        }
    }
}

int main()
{
    int vertices = 0;
    // vector<vector<int>> list = adjacencyList(vertices);
    // cout << endl;
    // printList(list);
    vector<int> parent;
    vector<int> size;
    vector<Edge> Edge = listEdge(vertices);
    // sort(Edge);
    // cout << endl;
    // for(int i=0; i<Edge.size(); i++)
    //     cout << Edge[i].u << " " << Edge[i].v << " "<< Edge[i].w << endl;
    make_set(parent, size, vertices);
    Kruskal(Edge, vertices, parent);
}