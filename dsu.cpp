#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

//---------------- Visualization ----------------//
void visualizeDSU(vector<int> &parent,
                  vector<int> &value,
                  string valueName,
                  string fileName)
{
    ofstream file(fileName);

    file << "digraph G {\n";
    file << "rankdir=TB;\n";
    file << "nodesep=0.6;\n";
    file << "ranksep=0.8;\n";

    // Nodes
    for (int i = 0; i < parent.size(); i++)
    {
        if (parent[i] == i)
        {
            file << i
                 << " [shape=circle, style=filled, fillcolor=yellow,"
                 << " label=\""
                 << i
                 << "\\nParent=" << parent[i]
                 << "\\n" << valueName << "=" << value[i]
                 << "\"];\n";
        }
        else
        {
            file << i
                 << " [shape=circle, style=filled, fillcolor=lightblue,"
                 << " label=\""
                 << i
                 << "\\nParent=" << parent[i]
                 << "\\n" << valueName << "=" << value[i]
                 << "\"];\n";
        }
    }

    // Parent Links
    for (int i = 0; i < parent.size(); i++)
    {
        if (parent[i] != i)
        {
            file << parent[i]
                 << " -> "
                 << i
                 << " [color=blue, penwidth=2];\n";
        }
    }

    file << "}\n";
    file.close();

    string png = fileName.substr(0, fileName.find('.')) + ".png";

    string cmd = "dot -Tpng " + fileName + " -o " + png;
    system(cmd.c_str());

    string open = "start " + png;
    system(open.c_str());
}
//---------------- Union By Size ----------------//

vector<int> parent;
vector<int> Size;

int find(int x)
{
    if (parent[x] == x)
        return x;

    return parent[x] = find(parent[x]);
}

void unionBySize(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a == b)
        return;

    if (Size[a] >= Size[b])
    {
        parent[b] = a;
        Size[a] += Size[b];
    }
    else
    {
        parent[a] = b;
        Size[b] += Size[a];
    }
}

//---------------- Union By Rank ----------------//

vector<int> parentRank;
vector<int> Rank;

int findRank(int x)
{
    if (parentRank[x] == x)
        return x;

    return parentRank[x] = findRank(parentRank[x]);
}

void unionByRank(int a, int b)
{
    a = findRank(a);
    b = findRank(b);

    if (a == b)
        return;

    if (Rank[a] < Rank[b])
    {
        parentRank[a] = b;
    }
    else if (Rank[a] > Rank[b])
    {
        parentRank[b] = a;
    }
    else
    {
        parentRank[b] = a;
        Rank[a]++;
    }
}

//---------------- Main ----------------//

int main()
{
    int n = 8;

    parent.resize(n);
    Size.resize(n, 1);

    parentRank.resize(n);
    Rank.resize(n, 0);

    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        parentRank[i] = i;
    }

    //---------------- Union By Size ----------------//

    unionBySize(1, 0);
    unionBySize(3, 2);
    unionBySize(3, 1);
    unionBySize(5, 4);
    unionBySize(3, 5);

    visualizeDSU(parent, Size, "Size", "dsuSize.dot");

    //---------------- Union By Rank ----------------//

     unionByRank(1, 0);
     unionByRank(2, 3);
     unionByRank(2, 1);
     unionByRank(5, 4);
     unionByRank(4, 2);
visualizeDSU(parentRank, Rank, "Rank", "dsuRank.dot");

    return 0;
}