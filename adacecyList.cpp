#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <unordered_set>
#include <cstdlib>
using namespace std;

int V;
vector<unordered_map<int,int>> graph;

// true = Directed
// false = Undirected
bool graphDirected = false;

//---------------- Add Edge ----------------//
void addEdge(int source, int destination, int weight)
{
    graph[source][destination] = weight;

    if (!graphDirected)
        graph[destination][source] = weight;
}

//---------------- Display ----------------//
void display()
{
    cout << "\nAdjacency Map\n\n";

    for(int i=0;i<V;i++)
    {
        cout << i << " -> ";

        for(auto edge : graph[i])
        {
            cout << "(" << edge.first << "," << edge.second << ") ";
        }

        cout << endl;
    }
}

//---------------- Visualization ----------------//
void visualizeGraph(string fileName="graph.dot")
{
    ofstream file(fileName);

    file<<"digraph G {\n";

    // Layout
    file<<"layout=dot;\n";
    file<<"rankdir=LR;\n";

    file<<"size=\"25,18!\";\n";
    file<<"dpi=300;\n";

    file<<"nodesep=2.0;\n";
    file<<"ranksep=2.5 equally;\n";

    file<<"splines=true;\n";
    file<<"overlap=false;\n";
    file<<"concentrate=false;\n";
    file<<"margin=0.5;\n";

    // Nodes
    for(int i=0;i<V;i++)
    {
        file<<i
            <<" [shape=circle,"
            <<"style=filled,"
            <<"fillcolor=lightblue,"
            <<"color=black,"
            <<"penwidth=2,"
            <<"width=0.9,"
            <<"height=0.9,"
            <<"fontsize=20];\n";
    }

    unordered_set<string> vis;

    // Edges
    for(int i=0;i<V;i++)
    {
        for(auto edge : graph[i])
        {
            int destination = edge.first;
            int weight = edge.second;

            if(graphDirected)
            {
                file<<i<<" -> "<<destination
                    <<" [label=\""<<weight
                    <<"\",color=red,"
                    <<"fontcolor=red,"
                    <<"fontsize=18,"
                    <<"penwidth=2.5,"
                    <<"arrowsize=1.4];\n";
            }
            else
            {
                string id1=to_string(i)+"-"+to_string(destination);
                string id2=to_string(destination)+"-"+to_string(i);

                if(vis.count(id1)||vis.count(id2))
                    continue;

                file<<i<<" -> "<<destination
                    <<" [dir=none,"
                    <<"label=\""<<weight
                    <<"\",color=blue,"
                    <<"fontcolor=blue,"
                    <<"fontsize=18,"
                    <<"penwidth=2.5];\n";

                vis.insert(id1);
            }
        }
    }

    file<<"}\n";
    file.close();

    string png=fileName.substr(0,fileName.find('.'))+".png";

    string cmd1="dot -Tpng "+fileName+" -o "+png;
    system(cmd1.c_str());

    string cmd2="start "+png;
    system(cmd2.c_str());
}

//---------------- Main ----------------//
int main()
{
    V=6;

    graph.resize(V);

    cout<<"Enter Graph Type (1=Directed, 0=Undirected): ";
    cin>>graphDirected;

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