#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct DegreeDirectedGraph
{
	int in_degree;
	int out_degree;
};

void printArray2D(int** a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
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

int** readAdjacencyList(const char* filename, int &vertices)
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

bool isDirectedGraph(int** matrix, int vertices)
{
	for (int i = 0; i < vertices; i++)
	{
		for (int j = i+1; j < vertices; j++)
		{
			if (matrix[i][j] != matrix[j][i])
				return true;
		}
	}
	return false;
}

vector<DegreeDirectedGraph> degreeOfDirectedGraph(int** matrix, int vertices)
{
	vector<DegreeDirectedGraph> degree(vertices);
	for (int k = 0; k < vertices; k++)
	{
		degree[k].in_degree = 0;
		degree[k].out_degree = 0;
	}

	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			if (matrix[i][j] == 1)
			{
				degree[i].out_degree++;
				degree[j].in_degree++;
			}
		}
	}
	return degree;
}

vector<int> degreeOfUndirectedGraph(int** matrix, int vertices)
{
	vector<int> degree;
	for (int i = 0; i < vertices; i++)
	{
		degree.push_back(0);
		for (int j = 0; j < vertices; j++)
		{
			if (matrix[i][j] == 1)
				degree[i]++;
		}
	}
	return degree;
}

int numberOfEdges(int **matrix, int vertices)
{
	if (isDirectedGraph(matrix, vertices))
	{
		vector<DegreeDirectedGraph> degree = degreeOfDirectedGraph(matrix, vertices);
		int count = 0;
		for (int i = 0; i < degree.size(); i++)
			count += degree[i].in_degree + degree[i].out_degree;
		return count / 2;
	}
	else
	{
		vector<int> degree = degreeOfUndirectedGraph(matrix, vertices);
		int count = 0;
		for (int i = 0; i < degree.size(); i++)
			count += degree[i];
		return count / 2;
	}
}

vector<int> isolatedVertices(int** matrix, int vertices)
{
	vector<int> isolated;
	if (isDirectedGraph(matrix, vertices))
	{
		vector<DegreeDirectedGraph> degree = degreeOfDirectedGraph(matrix, vertices);
		for (int i = 0; i < degree.size(); i++)
		{
			if (degree[i].in_degree + degree[i].out_degree == 0)
				isolated.push_back(i);
		}
	}
	else
	{
		vector<int> degree = degreeOfUndirectedGraph(matrix, vertices);
		for (int i = 0; i < degree.size(); i++)
		{
			if (degree[i] == 0)
				isolated.push_back(i);
		}
	}
	return isolated;
}

vector<int> leafVertices(int** matrix, int vertices)
{
	vector<int> leaf;
	if (isDirectedGraph(matrix, vertices))
	{
		vector<DegreeDirectedGraph> degree = degreeOfDirectedGraph(matrix, vertices);
		for (int i = 0; i < degree.size(); i++)
		{
			if (degree[i].in_degree + degree[i].out_degree == 1)
				leaf.push_back(i);
		}
	}
	else
	{
		vector<int> degree = degreeOfUndirectedGraph(matrix, vertices);
		for (int i = 0; i < degree.size(); i++)
		{
			if (degree[i] == 1)
				leaf.push_back(i);
		}
	}
	return leaf;
}

bool isCompleteGraph(int** matrix, int vertices)
{
	if (isDirectedGraph(matrix, vertices))
		return false;
	int count = 0;
	for (int i = 1; i < vertices; i++)
	{
		for (int j = i+1; j < vertices; j++)
		{
			if (matrix[i][j] == 1)
				count++; // số cạnh
		}
	}
	if (count == (vertices * (vertices + 1) / 2))
		return true;
	return false;
}

int main()
{
	const char* filename1 = "graph1.txt";
	const char* filename2 = "graph2.txt";
	vector<vector<int>> list = readAdjacencyMatrix(filename1);
	printList(list);
	//int vertices = 0;
	//int** matrix = readAdjacencyList(filename2, vertices); //tính verices number
	//printArray2D(matrix, vertices);

	/*if (isDirectedGraph(matrix, vertices))
		cout << "Do thi co huong" << endl;
	else
		cout << "Do thi vo huong" << endl;

	cout << "So canh cua do thi da cho la: " << numberOfEdges(matrix,vertices) << endl;*/

	/*vector<DegreeDirectedGraph> degree = degreeOfDirectedGraph(matrix, vertices);
	for (int i = 0; i < degree.size(); i++)
	{
		cout << "Dinh " << i << ": " << degree[i].in_degree << "," << degree[i].out_degree << endl;
	}*/

	/*vector<int> degree = degreeOfUndirectedGraph(matrix, vertices);
	for (int i = 0; i < degree.size(); i++)
	{
		cout << "Dinh " << i << ": " << degree[i] << endl;
	}*/

	/*vector<int> insolated = isolatedVertices(matrix, vertices);
	for (int i = 0; i < insolated.size(); i++)
	{
		cout << "Dinh co lap: " << insolated[i] << endl;
	}

	vector<int> leaf = leafVertices(matrix, vertices);
	for (int i = 0; i < leaf.size(); i++)
	{
		cout << "Dinh la: " << leaf[i] << endl;
	}*/
	
	/*if (isCompleteGraph(matrix, vertices))
		cout << "Do thi hoan chinh";
	else
		cout << "Do thi khong hoan chinh";*/

}