#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

class GraphMatrix 
{
    private:
    vector<vector<bool>> matrix;
    vector<string> mvertices; //names of vertices
    int V = 0; // number of vertices;
    bool is_directed;

    int index_of_vertex(const string &vertex) const;
    void add_vertex_gen(string vertex);
    void add_edge_gen(string vertex1, string vertex2);
    void delete_edge_gen(string vertex1, string vertex2);
    void delete_vertex_gen (string vertex);
    void DFS (int v, vector<bool> &visited);

    public:
    GraphMatrix(bool directed = false) : is_directed(directed) {}
    void print_matrix();
    void add_vertex();
    void add_edge();
    void delete_vertex();
    void delete_edge();
    bool is_connected();
    int shortest_path(string start, string end);
};

void GraphMatrix:: print_matrix ()
{
    for (int i = 0; i < V; i++)
    {
        cout << "{ ";
        for (int j = 0; j < V; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << "}" << endl;
    }
}

int GraphMatrix:: index_of_vertex (const string &vertex) const
{
    auto ind = find(mvertices.begin(), mvertices.end(), vertex);
    if (ind != mvertices.end())
    {
        return distance(mvertices.begin(), ind);
    }
    return -1; //if vertex wasn't found (do not exists)
}

void GraphMatrix:: delete_edge_gen (string vertex1, string vertex2)
{
    int ind1 = index_of_vertex(vertex1);
    int ind2 = index_of_vertex(vertex2);
    if (ind1 == -1 or ind2 == -1)
    {
        cout << "One or both vertices do not exist! Please try again" << endl;
        return;
    }
    matrix[ind1][ind2] = 0;
    if (!is_directed)
    {
        matrix[ind2][ind1] = 0;
    }
}

void GraphMatrix:: delete_edge ()
{
    string vertex1, vertex2;
    cout << "Type in the first vertex" << endl;
    cin >> vertex1;
    cout << "Type in the second vertex" << endl;
    cin >> vertex2;
    delete_edge_gen(vertex1, vertex2);
}

void GraphMatrix:: add_vertex_gen (string vertex)
{
    int ind = index_of_vertex(vertex);
    if (ind != -1)
    {
        cout << "This vertex already exists! Please try again." << endl;
        return;
    }

    V++;
    matrix.resize(V);
    mvertices.push_back(vertex);
    for (int i = 0; i < V; i++)
    {
        matrix[i].resize(V, 0);
    }
}

void GraphMatrix:: add_vertex ()
{
    string vertex;
    cout << "Type in vertex you want to add" << endl;
    cin >> vertex;
    add_vertex_gen (vertex);

    int answer;
    cout << "Choose the type of vertex do you want to add  Enter:\n 1 - isolated\n 2 - connected to existimh vertex\n ";
    cout << "3 - between two existing vertices" << endl;
    cin >> answer;
    if (answer != 1 and answer != 2 and answer != 3 )
    {
        cout << "Incorrect input! Please try again." << endl;
    }
    else if (answer == 2)
    {
        string newvertex;
        cout << "Type in the vertex which you want to connect with the new one" << endl;
        cin >> newvertex;
        int ind = index_of_vertex(newvertex);
        if (ind == -1)
        {
            cout << "This vertex does not exist!" << endl;
            return;
        }
        else
        {
             add_edge_gen(newvertex, vertex);
        }
    }
    else if (answer == 3)
    {
        string newver1, newver2;
        cout << "Type in the first vertex which is connected to the new one" << endl;
        cin >> newver1;
        cout << "Type in the second vertex which is connected to the new one" << endl;
        cin >> newver2;
        int ind1 = index_of_vertex(newver1);
        int ind2 = index_of_vertex(newver2);
        if (ind1 == -1 or ind2 == -1)
        {
            cout << "One or both of vertices does not exist! Please try again. " << endl;
        }
        else 
        {
            delete_edge_gen(newver1, newver2);
            add_edge_gen(vertex, newver1);
            add_edge_gen(vertex, newver2);
        }
    }
}

void GraphMatrix:: add_edge_gen (string vertex1, string vertex2)
{
    int ind1 = index_of_vertex(vertex1); 
    int ind2 = index_of_vertex(vertex2);
    if (ind1 == -1 or ind2 == -1)
    {
        cout << "One or both vertices do not exist! Please try again" << endl;
        return;
    }
    matrix[ind1][ind2] = true;
    if (!is_directed)
    {
        matrix[ind2][ind1] = true;
    }

}

void GraphMatrix:: add_edge()
{
    string vertex1, vertex2;
    cout << "Type in the first vertex" << endl;
    cin >> vertex1;
    cout << "Type in the second vertex" << endl;
    cin >> vertex2;
    add_edge_gen(vertex1, vertex2);
}

void GraphMatrix:: delete_vertex_gen (string vertex)
{
    int ind = index_of_vertex(vertex);
    if (ind == -1)
    {
        cout << "This vertex does not exist  Please try again. " << endl;
    }
    else 
    {
        V--;
        matrix.erase(matrix.begin() + ind);
        for (int i = 0; i < matrix.size(); ++i) 
        {
            matrix[i].erase(matrix[i].begin() + ind);
        }
        mvertices.erase(mvertices.begin() + ind);
    }
}

void GraphMatrix:: delete_vertex()
{
    string vertex;
    cout << "Type in the vertex you want to delete" << endl;
    cin >> vertex;
    delete_vertex_gen (vertex);
}

void GraphMatrix:: DFS(int v, vector<bool> &visited)
{
    visited[v] = true;
    for (int current = 0; current < V; current++)
    {
        if (matrix[v][current] == 1 and !visited[current])
        {
            DFS(current, visited);
        }
    }
}

bool GraphMatrix:: is_connected ()
{
    vector<bool> visited(V, false);
    DFS(0, visited);
    for (int i = 0; i < V; i++)
    {
        if (!visited [i])
        {
            return false;
        }
    }
    return true;
}

int GraphMatrix:: shortest_path (string start, string end)
{
    if (start == end)
    {
        return 0;
    } 

    int ind1 = index_of_vertex(start);
    int ind2 = index_of_vertex(end);
    if (ind1 == -1 or ind2 == -1)
    {
        cout << "One or both vertices do not exist! Please try again." << endl;
        return -1;
    }

    queue<int> q;
    vector<int> Distance(V, -1);
    vector<bool> visited(V, false);

    q.push(ind1);
    Distance[ind1] = 0;
    visited[ind1] = true;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        for(int i = 0; i < V; i++)
        {
            if(matrix[current][i] == 1 and !visited[i])
            {
                visited[i] = true;
                Distance[i] = Distance[current] + 1;
                if (i == ind2)
                {
                    return Distance[i];
                }
                q.push(i);
            }
        }

    }
    return -1; //path was not found
}