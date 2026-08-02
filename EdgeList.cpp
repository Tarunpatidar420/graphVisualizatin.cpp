#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <cstdlib>

using namespace std;


//---------------- Edge Structure ----------------//

struct Edge
{
    int destination;
    int weight;
    bool directed;
};


//---------------- Graph Class ----------------//

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


    // directed = true  -> Directed
    // directed = false -> Undirected

    void addEdge(int source, int destination, int weight, bool directed)
    {
        adj[source].push_back({destination, weight, directed});


        // Undirected graph ke liye reverse edge
        if(!directed)
        {
            adj[destination].push_back({source, weight, directed});
        }
    }



    void display()
    {
        cout << "\nAdjacency List\n\n";


        for(int i=0;i<V;i++)
        {
            cout << i << " -> ";


            for(auto e : adj[i])
            {
                cout << "("
                     << e.destination
                     << ","
                     << e.weight
                     << ","
                     << (e.directed ? "D":"U")
                     << ") ";
            }


            cout << endl;
        }
    }

};




//---------------- Visualization Function Outside Class ----------------//

void visualizeGraph(Graph &g, string fileName="graph.dot")
{

    ofstream file(fileName);


    file<<"digraph G {\n";


    // Graph Layout

    file<<"layout=dot;\n";
    file<<"rankdir=LR;\n";

    file<<"size=\"22,16!\";\n";
    file<<"dpi=300;\n";

    file<<"nodesep=1.8;\n";
    file<<"ranksep=2.2;\n";

    file<<"splines=true;\n";
    file<<"overlap=false;\n";
    file<<"concentrate=false;\n";



    // Nodes

    for(int i=0;i<g.V;i++)
    {
        file<<i
            <<" [shape=circle,"
            <<"style=filled,"
            <<"fillcolor=lightblue,"
            <<"color=black,"
            <<"penwidth=2,"
            <<"width=0.8,"
            <<"height=0.8,"
            <<"fontsize=18];\n";
    }



    vector<vector<bool>> visited(g.V,
                         vector<bool>(g.V,false));



    // Edges

    for(int i=0;i<g.V;i++)
    {

        for(auto e : g.adj[i])
        {

            int dest = e.destination;


            // Directed Edge

            if(e.directed)
            {

                file<<i<<" -> "<<dest
                    <<" [label=\""<<e.weight
                    <<"\","
                    <<"color=red,"
                    <<"fontcolor=red,"
                    <<"penwidth=2.5,"
                    <<"fontsize=16,"
                    <<"arrowsize=1.3];\n";

            }


            // Undirected Edge

            else
            {

                if(!visited[i][dest] &&
                   !visited[dest][i])
                {

                    file<<i<<" -> "<<dest
                        <<" [dir=none,"
                        <<"label=\""<<e.weight
                        <<"\","
                        <<"color=blue,"
                        <<"fontcolor=blue,"
                        <<"penwidth=2.5,"
                        <<"fontsize=16];\n";


                    visited[i][dest]=true;
                    visited[dest][i]=true;

                }

            }

        }

    }



    file<<"}\n";


    file.close();



    string png = fileName.substr(0,fileName.find('.'))+".png";


    string cmd1="dot -Tpng "+fileName+" -o "+png;

    system(cmd1.c_str());



    string cmd2="start "+png;

    system(cmd2.c_str());

}



//---------------- Main ----------------//

int main()
{

    Graph g(6);



    // source , destination , weight , directed


    g.addEdge(0,1,5,false);   // Undirected

    g.addEdge(0,4,3,true);    // Directed

    g.addEdge(1,3,7,false);   // Undirected

    g.addEdge(3,4,4,true);    // Directed

    g.addEdge(4,5,2,false);   // Undirected

    g.addEdge(3,5,6,true);    // Directed



    g.display();



    visualizeGraph(g);



    return 0;
}
