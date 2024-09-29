#include <iostream>
#include "classes/GraphAdjList.h"
using namespace std;

int main ()
{
    GraphAdjList Places;
    Places.add_vertex();
    Places.add_vertex();
    Places.add_vertex();
    Places.add_vertex();

    Places.print_graph();
    Places.delete_vertex();
    Places.print_graph();
    Places.delete_edge();
    Places.print_graph();
    if (!Places.is_connected())
        cout << "FALSE " << endl;
    else
        cout << "TRUE" << endl;
    return 0;
}