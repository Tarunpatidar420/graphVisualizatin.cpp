#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <cstdlib>
using namespace std;

int V;
vector<vector<pair<int,int>>> graph;

// true = Directed
// false = Undirected
bool graphDirected = false;

//---------------- Add Edge ----------------//
void addEdge(int source, int destination, int weight)
{
    graph[source][destination] = {1, weight};

    if (!graphDirected)
    {
        graph[destination][source] = {1, weight};
    }
}

//---------------- Display ----------------//
void display()
{
    cout << "\nAdjacency Matrix (Exist, Weight)\n\n";

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << "("
                 << graph[i][j].first << ","
                 << graph[i][j].second << ") ";
        }
        cout << endl;
    }
}

//---------------- Visualization ----------------//
void visualizeGraph(string fileName = "graph.dot")
{
    ofstream file(fileName);

    file << "digraph G {\n";

    // Graph Layout
    file << "layout=dot;\n";
    file << "rankdir=LR;\n";
    file << "size=\"20,14!\";\n";
    file << "dpi=300;\n";
    file << "nodesep=1.8;\n";
    file << "ranksep=2.0 equally;\n";
    file << "splines=true;\n";
    file << "overlap=false;\n";
    file << "concentrate=false;\n";
    file << "margin=0.4;\n";

    // Nodes
    for (int i = 0; i < V; i++)
    {
        file << i
             << " [shape=circle,"
             << " style=filled,"
             << " fillcolor=lightblue,"
             << " color=black,"
             << " penwidth=2,"
             << " width=0.8,"
             << " height=0.8,"
             << " fontsize=18];\n";
    }

    unordered_set<string> vis;

    // Edges
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (graph[i][j].first == 0)
                continue;

            int weight = graph[i][j].second;

            if (graphDirected)
            {
                file << i << " -> " << j
                     << " [label=\"" << weight
                     << "\", color=red,"
                     << " penwidth=2.5,"
                     << " fontsize=16,"
                     << " arrowsize=1.3];\n";
            }
            else
            {
                string id1 = to_string(i) + "-" + to_string(j);
                string id2 = to_string(j) + "-" + to_string(i);

                if (vis.count(id1) || vis.count(id2))
                    continue;

                file << i << " -> " << j
                     << " [dir=none,"
                     << " label=\"" << weight
                     << "\", color=blue,"
                     << " penwidth=2.5,"
                     << " fontsize=16];\n";

                vis.insert(id1);
            }
        }
    }

    file << "}\n";
    file.close();

    string png = fileName.substr(0, fileName.find('.')) + ".png";

    string cmd1 = "dot -Tpng " + fileName + " -o " + png;
    system(cmd1.c_str());

    string cmd2 = "start " + png;
    system(cmd2.c_str());
}

//---------------- Main ----------------//
int main()
{
    V = 6;

    graph.resize(V, vector<pair<int,int>>(V, {0,0}));

    cout << "Enter Graph Type (1 = Directed, 0 = Undirected): ";
    cin >> graphDirected;

    addEdge(0,1,5);
    addEdge(0,2,2);
    addEdge(1,3,8);
    addEdge(2,4,4);
    addEdge(3,5,7);
    addEdge(4,5,1);

    display();

    visualizeGraph();

    return 0;
}
