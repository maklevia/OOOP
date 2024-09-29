#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;


//-------------------Graph Adjacency List---------------------------
class GraphAdjList
{
    private:
    int V = 0; //number of vertices
    vector <vector<int>> adj_list; //adjacency list
    vector <string> vertices; //this graph store string data in vertices
    
    int find_vertex_index(const string &vertex) const;
    void add_edge_gen(string vertex1, string vertex2);
    void delete_vertex_gen(string vertex1);
    void delete_edge_gen(string vertex1, string vertex2);
    void DFS(int v, bool is_visited[]);
    
    public:
    void add_vertex ();
    void delete_vertex();
    void add_edge ();
    void delete_edge ();
    void print_graph();
    bool is_connected();
    int shortest_path(string start, string end);
};

int GraphAdjList::find_vertex_index(const string &vertex) const
{
    auto ind = find(vertices.begin(), vertices.end(), vertex);
    if(ind != vertices.end())
    {
        return distance(vertices.begin(), ind);
    }
    return -1; //if vertex wasn't found (do not exists)
}

void GraphAdjList::delete_edge_gen(string vertex1, string vertex2)
{
    int ind1 = find_vertex_index(vertex1);
    int ind2 = find_vertex_index(vertex2);
    if (ind1 == -1 or ind2 == -1)
    {
        cout << "ERROR" << endl;
        return;
    }
    adj_list[ind1].erase(remove(adj_list[ind1]. begin(), adj_list[ind1].end(), ind2), adj_list[ind1].end());
    adj_list[ind2].erase(remove(adj_list[ind2]. begin(), adj_list[ind2].end(), ind1), adj_list[ind2].end());
}
    
void GraphAdjList::delete_vertex_gen(string vertex)
{
    int ind = find_vertex_index(vertex);
    if (ind == -1)
    {
        cout << "This vertex does not exist!" << endl;
        return;
    }
    for (int i = 0; i < V; i++)
    {
        adj_list[i].erase(remove(adj_list[i].begin(), adj_list[i].end(), ind), adj_list[i].end());
    }
    vertices.erase(vertices.begin() + ind);
    adj_list.erase(adj_list.begin() + ind);
    
    V--;
    
    for (auto &neighbours : adj_list)
    {
        for (auto &indexx : neighbours)
        {
            if (indexx > ind)
            {
                indexx--;
            }
        }
    }
}

void GraphAdjList::DFS(int v, bool is_visited[])
{
    is_visited[v] = true;
    for (int current : adj_list[v])
    {
        if (!is_visited[current])
        {
            DFS(current, is_visited);
        }
    }
}

bool GraphAdjList::is_connected()
{
    bool is_visited[] = {false};
    DFS(0, is_visited);
    for (int i = 0; i < V; i++)
    {
        if (!is_visited[i])
        {
            return false;
        }
    }
    return true;
}

void GraphAdjList::print_graph()
{
    for (int i = 0; i < V; i++)
    {
        cout << vertices[i] << ": ";
        for (auto j = adj_list[i].begin(); j != adj_list[i].end(); j++)
        {
            cout << vertices[*j] << ", ";
        }
        cout << endl;
    }
}

void GraphAdjList::delete_vertex()
{
    string vertex;
    cout << "Type in the vertex you want to remove " << endl;
    cin >> vertex;
    delete_vertex_gen(vertex);
}

void GraphAdjList::delete_edge()
{
    string vertex1, vertex2;
    cout << "Enter two vertices between which edge should be deleted" << endl;
    cin >> vertex1;
    cin >> vertex2;
    delete_edge_gen(vertex1, vertex2);
}

void GraphAdjList::add_edge_gen(string vertex1, string vertex2)
{
    int ind1 = find_vertex_index(vertex1);
    int ind2 = find_vertex_index(vertex2);
    if (ind1 == -1 or ind2 == -1)
    {
        cout << "ERROR" << endl;
        return;
    }
    adj_list[ind2].push_back(ind1);
    adj_list[ind1].push_back(ind2);
}

void GraphAdjList::add_edge () //this class is used for Places, therefore it's undirected
{
    string vertex1, vertex2;
    cout << "Enter first of the vertices you want to connect" << endl;
    cin >> vertex1;
    cout << "Enter second of the vertices you want to connect" << endl;
    cin >> vertex2;
    add_edge_gen(vertex1, vertex2);
}

void GraphAdjList::add_vertex ()
{
    string vertex;
    cout << "Print the vertex you want to add" << endl;
    cin >> vertex;
    int ind = find_vertex_index(vertex);
    if (ind != -1)
    {
        cout << "This vertex already exists! Please print a new vertex" << endl;
        return;
    }
    vertices.push_back(vertex);
    adj_list.push_back({});
    V++;
        int answer;
        cout << "Choose to which excisting vertices you want to connect the new one. Type \n 1 - isolated vertex\n 2 - connected to an excisting vertex\n 3 - between two excisting vertices" << endl;
        cin >> answer;

        if (answer != 1 and answer != 2 and answer != 3 )
    {
        cout << "Incorrect input! Please try again." << endl;
    }
            if (answer == 2)
            {
                string vertex1;
                cout << "Enter the vertex to which this one is connected: " << endl;
                cin >> vertex1;
                int ind = find_vertex_index(vertex1);
                if (ind == -1)
                {
                    cout << "This vertex does not exist!" << endl;
                    return;
                }
                else
                {
                    add_edge_gen(vertex, vertex1);
                }
            }
            else if (answer == 3)
            {
                string vertex1, vertex2;
                cout << "Enter the first vertex" << endl;
                cin >> vertex1;
                cout << "Enter the second vertex" << endl;
                cin >> vertex2;
                int ind1 = find_vertex_index(vertex1);
                int ind2 = find_vertex_index(vertex2);
                if (ind1 == -1 or ind2 == -1)
                {
                    cout << "ERROR" << endl;
                    return;
                }
                else
                {
                    delete_edge_gen(vertex1, vertex2);
                    add_edge_gen(vertex, vertex1);
                    add_edge_gen(vertex, vertex2);
                }
            }
}

int GraphAdjList::shortest_path (string start, string end)
{
    if (start == end)
    {
        return 0;
    }
    int ind1 = find_vertex_index(start);
    int ind2 = find_vertex_index(end);
    if (ind1 == -1 or ind2 == -1)
    {
        cout << "Incorrect input. Please try again." << endl;
        return -1;
    }
    queue<int> q;
    q.push(ind1);

    vector <bool> visited(V, false);
    vector <int> Distance(V, -1);

    visited[ind1] = true;
    Distance[ind1] = 0;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        for (int i : adj_list[current])
        {
            if (!visited[i])
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
    return -1; //if path wasn't found
}