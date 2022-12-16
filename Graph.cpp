#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

void printList(vector<vector<int>> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		for (int j = 0; j < list[i].size(); j++)
			cout << list[i][j] << " ";
		cout << endl;
	}
}

vector<vector<int>> readAdjacencyMatrix(const char* filename)
{
	vector<vector<int>> list;
	fstream fin(filename, ios::in);
	if (!fin)
	{
		cout << "Mo file khong thanh cong" << endl;
		return list;
	}
	cout << "Mo file thanh cong" << endl;

	int vertices = 0;
	fin >> vertices;
	int** matrix = new int* [vertices];

	for (int i = 0; i < vertices; i++)
	{
		matrix[i] = new int[vertices];
		for (int j = 0; j < vertices; j++)
		{
			fin >> matrix[i][j];
		}
	}

	//output the information of the corresponding Adjacency matrix
	for (int m = 0; m < vertices; m++)
	{
		vector<int> adj_list;
		for (int n = 0; n < vertices; n++)
		{
			if (matrix[m][n] == 1)
				adj_list.push_back(n);
		}
		list.push_back(adj_list);
	}

	fin.close();
	return list;
}

int** readAdjacencyList(const char* filename, int& vertices)
{
	fstream fin(filename, ios::in);
	if (!fin)
	{
		cout << "Mo file khong thanh cong" << endl;
		return NULL;
	}
	cout << "Mo file thanh cong" << endl;

	string snumber;
	getline(fin, snumber);
	vertices = stoi(snumber);
	vector<vector<int>> list(vertices);
	for (int i = 0; i < list.size(); i++)
	{
		string buffer;
		getline(fin, buffer);
		istringstream line_number(buffer);
		int number = 0;
		while (line_number >> number)
		{
			list[i].push_back(number);
		}
	}

	int** matrix = new int* [vertices];
	for (int i = 0; i < vertices; i++)
	{
		matrix[i] = new int[vertices];
		for (int j = 0; j < vertices; j++)
		{
			matrix[i][j] = 0;
		}
		for (int k = 0; k < list[i].size(); k++)
			matrix[i][list[i][k]] = 1;
	}
	return matrix;
	fin.close();
}

vector<vector<int>> adjacencyList(int &vertices)
{
	int n = 0; int m = 0;
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

vector<int> Visited(int vertices)
{
	vector<int> visited;
	for (int i = 0; i < vertices; i++)
		visited.push_back(0);
	return visited;
}

void DFS(int u,vector<vector<int>> list, vector<int> &visited)
{
	cout << u << " ";
	visited[u] = 1;
	for (int v : list[u])
	{
		if (visited[v]==0)
			DFS(v, list, visited);
	}
}

void BFS(int u, vector<vector<int>> list, vector<int>& visited)
{
	queue<int> q;
	q.push(u);
	visited[u] = 1;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		cout << v << " ";
		for (int i=0; i<list[v].size(); i++)
		{
			if (visited[list[v][i]] == 0)
			{
				q.push(list[v][i]);
				visited[list[v][i]] = 1;
			}
		}
	}
}

void dfs(int u, vector<vector<int>> list, vector<int>& visited)
{
	visited[u] = 1;
	for (int v : list[u])
	{
		if (visited[v] == 0)
			dfs(v, list, visited);
	}
}

void connectedComponent(vector<vector<int>> list, vector<int>& visited)
{
	int cnt = 0;
	for (int i = 0; i < list.size(); i++)
	{
		if (visited[i] == 0)
		{
			cout << "Thanh phan thu " << cnt << ": ";
			DFS(i, list, visited);
			cnt++;
		}
	}
	//cout << cnt << " "
}

int main()
{
	/*const char* filename1 = "graph1.txt";
	const char* filename2 = "graph2.txt";
	int vertices = 0;
	vector<vector<int>> list = readAdjacencyMatrix(filename1);
	int** matrix = readAdjacencyList(filename2, vertices);
	printList(list);*/
	int vertices = 0;
	vector<vector<int>> list = adjacencyList(vertices);
	cout << endl;
	printList(list);
	cout << endl;
	vector<int> visited = Visited(vertices);
	connectedComponent(list, visited);
}