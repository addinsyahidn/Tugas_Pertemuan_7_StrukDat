#include <iostream>
#include <vector>
#include <climits>
#include <cctype>
using namespace std;

class Graph
{
private:
    int V;
    vector<vector<int>> adjMatrix;

public:
    Graph(int jumlahVertex)
    {
        V = jumlahVertex;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight)
    {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    // mencetak rute dari source ke vertex tujuan menggunakan array parent
    void printPath(vector<int> &parent, int tujuan)
    {
        if (parent[tujuan] == -1)
        {
            cout << char('A' + tujuan);
            return;
        }
        printPath(parent, parent[tujuan]);
        cout << " -> " << char('A' + tujuan);
    }

    void dijkstra(int source, int tujuan = -1)
    {
        vector<int> distance(V, INT_MAX);
        vector<int> parent(V, -1);
        vector<bool> visited(V, false);
        distance[source] = 0;

        for (int i = 0; i < V; i++)
        {
            int u = -1;

            for (int j = 0; j < V; j++)
            {
                if (!visited[j] &&
                    (u == -1 || distance[j] < distance[u]))
                {
                    u = j;
                }
            }

            if (u == -1 || distance[u] == INT_MAX)
                break;

            visited[u] = true;

            for (int v = 0; v < V; v++)
            {
                if (adjMatrix[u][v] != 0 && !visited[v])
                {
                    int newDistance = distance[u] + adjMatrix[u][v];

                    if (newDistance < distance[v])
                    {
                        distance[v] = newDistance;
                        parent[v] = u;
                    }
                }
            }
        }

        // tujuan = -1 : tampilkan rute ke semua lokasi
        if (tujuan == -1)
        {
            cout << "Rute terpendek dari lokasi " << char('A' + source) << ":" << endl;

            for (int i = 0; i < V; i++)
            {
                if (i == source)
                    continue;

                cout << char('A' + source) << " ke " << char('A' + i) << " : ";

                if (distance[i] == INT_MAX)
                {
                    cout << "Tidak terjangkau" << endl;
                }
                else
                {
                    printPath(parent, i);
                    cout << " (Total jarak: " << distance[i] << " km)" << endl;
                }
            }
        }
        // tujuan tertentu : tampilkan rekomendasi rute tercepat
        else
        {
            cout << "Rekomendasi rute tercepat "
                 << char('A' + source) << " ke " << char('A' + tujuan) << ":" << endl;

            if (distance[tujuan] == INT_MAX)
            {
                cout << "Tidak terjangkau" << endl;
            }
            else
            {
                cout << "Rute : ";
                printPath(parent, tujuan);
                cout << endl;
                cout << "Total jarak : " << distance[tujuan] << " km" << endl;
            }
        }
    }
};

int main()
{
    Graph graph(6); // lokasi A - F

    graph.addEdge(0, 1, 4); // A - B
    graph.addEdge(0, 2, 2); // A - C
    graph.addEdge(1, 2, 1); // B - C
    graph.addEdge(1, 3, 5); // B - D
    graph.addEdge(1, 4, 3); // B - E
    graph.addEdge(2, 3, 8); // C - D
    graph.addEdge(2, 4, 6); // C - E
    graph.addEdge(3, 4, 2); // D - E
    graph.addEdge(3, 5, 4); // D - F
    graph.addEdge(4, 5, 3); // E - F

    // 1. rute terpendek dari A ke semua lokasi
    graph.dijkstra(0);

    cout << endl;

    // 2. rekomendasi rute berdasarkan input pengguna
    char asal, tujuan;
    cout << "Masukkan lokasi asal (A-F)   : ";
    cin >> asal;
    cout << "Masukkan lokasi tujuan (A-F) : ";
    cin >> tujuan;

    asal = toupper(asal);
    tujuan = toupper(tujuan);

    if (asal < 'A' || asal > 'F' || tujuan < 'A' || tujuan > 'F')
    {
        cout << "Lokasi nonvalid" << endl;
        return 0;
    }

    cout << endl;
    graph.dijkstra(asal - 'A', tujuan - 'A');

    return 0;
}
