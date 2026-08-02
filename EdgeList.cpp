#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Edge
{
    int destination;
    int weight;
    bool directed;
};

class Graph
{
public:
    int V;
    vector<list<Edge>> adj;

    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    // Runtime par decide hoga Directed ya Undirected
    void addEdge(int source, int destination, int weight, bool directed)
    {
        adj[source].push_back({destination, weight, directed});

        // Agar undirected hai to reverse edge bhi add karo
        if (!directed)
        {
            adj[destination].push_back({source, weight, directed});
        }
    }

    void display()
    {
        cout << "\nAdjacency List\n\n";

        for (int i = 0; i < V; i++)
        {
            cout << i << " -> ";

            for (Edge e : adj[i])
            {
                cout << "("
                     << e.destination << ", "
                     << e.weight << ", "
                     << (e.directed ? "D" : "U")
                     << ") ";
            }

            cout << endl;
        }
    }

    void visualize(string fileName = "graph.dot")
    {
        ofstream file(fileName);

        file << "digraph G {\n";
        file << "rankdir=LR;\n";
        file << "nodesep=0.8;\n";
        file << "ranksep=1.0;\n";

        // Nodes
        for (int i = 0; i < V; i++)
        {
            file << i
                 << " [shape=circle, style=filled, fillcolor=lightblue];\n";
        }

        vector<vector<bool>> vis(V, vector<bool>(V, false));

        // Edges
        for (int i = 0; i < V; i++)
        {
            for (Edge e : adj[i])
            {
                if (e.directed)
                {
                    file << i << " -> " << e.destination
                         << " [label=\"" << e.weight
                         << "\", color=blue, penwidth=2];\n";
                }
                else
                {
                    if (!vis[i][e.destination] && !vis[e.destination][i])
                    {
                        file << i << " -> " << e.destination
                             << " [dir=none, label=\"" << e.weight
                             << "\", color=red, penwidth=2];\n";

                        vis[i][e.destination] = true;
                        vis[e.destination][i] = true;
                    }
                }
            }
        }

        file << "}\n";
        file.close();

        system("dot -Tpng graph.dot -o graph.png");
        system("start graph.png");
    }
};

int main()
{
    Graph g(6);

    // source, destination, weight, directed

    g.addEdge(0, 1, 5, false); // Undirected
    g.addEdge(0, 4, 3, true);  // Directed
    g.addEdge(1, 3, 7, false); // Undirected
    g.addEdge(3, 4, 4, true);  // Directed
  //  g.addEdge(4, 5, 2, false); // Undirected
   // g.addEdge(3, 5, 6, true);  // Directed

    g.display();

    g.visualize();

    return 0;
}