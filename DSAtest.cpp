#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
// #include <string.h>
using namespace std;

struct Animal
{
    string en;
    string vn;
    string ph;
    int loai;
};

struct Node
{
    int key;
    Animal data;
    Node *pLeft;
    Node *pRight;
};

int findKey(Animal data)
{
    int key = 0;
    for (int i = 0; i < data.en.size(); i++)
    {
        key += (int)data.en[i];
    }
    return key;
}

Node *createNode(Animal data)
{
    Node *p = new Node;
    p->data = data;
    p->pLeft = NULL;
    p->pRight = NULL;
    p->key = findKey(data);
    return p;
}

int height(Node *root)
{
    if (root == NULL)
        return 0;
    int left = height(root->pLeft);
    int right = height(root->pRight);
    return max(left, right) + 1;
}

int weight(Node *root)
{
    return height(root->pLeft) - height(root->pRight);
}

void rotateLeft(Node *&root)
{
    Node *b = root->pRight;
    Node *T2 = b->pLeft;
    b->pLeft = root;
    root->pRight = T2;
    root = b;
}

void rotateRight(Node *&root)
{
    Node *b = root->pLeft;
    Node *T2 = b->pRight;
    b->pRight = root;
    root->pLeft = T2;
    root = b;
}

void rotateLeftRight(Node *&root)
{
    rotateLeft(root->pLeft);
    rotateRight(root);
}

void rotateRightLeft(Node *&root)
{
    rotateRight(root->pRight);
    rotateLeft(root);
}

void Insert(Node *&root, Animal x)
{
    if (root == NULL)
    {
        Node *newNode = createNode(x);
        root = newNode;
        return;
    }
    if (findKey(x) > root->key)
        Insert(root->pRight, x);
    else if (findKey(x) < root->key)
        Insert(root->pLeft, x);
    else
        return;

    // cập nhật lại trọng số
    if (weight(root) > 1)
    {
        if (weight(root->pLeft) < 0)
            rotateLeftRight(root);
        else
            rotateRight(root);
    }
    else if (weight(root) < -1)
    {
        if (weight(root->pRight) > 0)
            rotateRightLeft(root);
        else
            rotateLeft(root);
    }
}

Animal readOneAnimal(ifstream &fin)
{
    Animal data;
    getline(fin, data.en, '\n');
    getline(fin, data.ph, '\n');
    getline(fin, data.vn, '\n');
    string buffer;
    getline(fin, buffer);
    data.loai = stoi(buffer);
    return data;
}

Node *readAnimals(string filename)
{
    Node *avl = new Node;
    avl = NULL;
    ifstream fin(filename, ios::in);
    // while (!fin.eof())
    // {
    //     Animal data;
    //     string buffer;
    //     getline(fin,buffer);
    //     data.en = buffer;
    //     getline(fin, buffer);
    //     data.ph = buffer;
    //     getline(fin, buffer);
    //     data.vn = buffer;
    //     getline(fin, buffer);
    //     data.loai = stoi(buffer);
    //     Insert(avl, data);
    //     continue;
    // }

    while (!fin.eof())
    {
        Animal data = readOneAnimal(fin);
        Insert(avl, data);
    }
    fin.close();
    return avl;
}

void printOneAnimal(Animal data)
{
    cout << data.en << endl;
    cout << data.ph << endl;
    cout << data.vn << endl;
    cout << data.loai << endl;
}

void LNR(Node *avl)
{
    if (avl == NULL)
        return;
    LNR(avl->pLeft);
    printOneAnimal(avl->data);
    LNR(avl->pRight);
}

void removeNode(Node *&root, string en)
{
}

int main()
{
    Node *avl = readAnimals("Animal.txt");
    LNR(avl);
}