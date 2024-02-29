#include <iostream>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <climits>
#include <windows.h>

using namespace std;
HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);

vector<string> v1 = {"Chroy Chongvar", "Prek Pnov",  "Russey Keo", "Sen Sok", "Por Senchey", "Kamboul", "Dangkao", "Mean Chey", "Toul Kouk", "Doun Penh", "Prampi Makara", "Chamkar Mon", "Boeng Kengkong", "Chbar Ampov"};

// A directed graph using adjacency list representation
class Graph {
    map<string, double> vertexMap;       // Map to store vertex names and their respective indices
    vector<list<pair<double, double>>> adj; // Adjacency list representing the graph.

public:
    void addVertex(string name);
    void addEdge(string u, string v, double weight);
    void printAllPaths(string s, string d);
    double shortestDistance(string s, string d);

private:
    vector<pair<double, int>> dijkstra(int src);
    int getMinDistanceVertex(vector<double>& dist, vector<bool>& visited);
};

void Graph::addVertex(string name) {
    int index = vertexMap.size(); // Assign new index to vertex
    vertexMap[name] = index;      // Map vertex name to index
    adj.push_back(list<pair<double, double>>{});  // Add new vertex to adjacency list
}

void Graph::addEdge(string u, string v, double weight)  {
    int uIndex = vertexMap[u];  // Get index of vertex u
    int vIndex = vertexMap[v];  // Get index of vertex v
    adj[uIndex].push_back(make_pair(vIndex, weight)); // Add v to u's adjacency list with weight
    adj[vIndex].push_back(make_pair(uIndex, weight)); // Add u to v's adjacency list with weight
}

vector<pair<double, int>> Graph::dijkstra(int src) {
    int V = adj.size();
    vector<double> dist(V, INT_MAX); // Initialize all distances as infinity
    vector<int> parent(V, -1);     // Initialize parent array
    dist[src] = 0;  // Distance from source vertex to itself is 0

    vector<bool> visited(V, false);  // Mark all vertices as not visited

    for (int i = 0; i < V-1; i++) {
        int u = getMinDistanceVertex(dist, visited);  // Get the vertex with minimum distance value
        
        visited[u] = true;  // Mark the picked vertex as visited

        // Update distance values of the adjacent vertices of the picked vertex
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = it->first;
            double weight = it->second;
            
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;  // Set parent of v as u
            }
        }
    }
    
    // Change return type to vector<pair<int, int>>
    vector<pair<double, int>> result;
    for (int i = 0; i < V; i++) {
        result.push_back(make_pair(dist[i], parent[i]));
    }
    return result;
}


int Graph::getMinDistanceVertex(vector<double>& dist, vector<bool>& visited) {
    int V = adj.size();
    int minDistance = INT_MAX;
    int minIndex;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= minDistance) {
            minDistance = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

double Graph::shortestDistance(string s, string d) {
    double src = vertexMap[s];
    double dest = vertexMap[d];

    vector<pair<double, int>> dist = dijkstra(src);
   return dist[dest].first;
}

void Graph::printAllPaths(string s, string d) {
    int src = vertexMap[s];
    int dest = vertexMap[d];

    vector<pair<double, int>> parent = dijkstra(src);

    if (parent[dest].first == INT_MAX) {
        SetConsoleTextAttribute(h,10);
        cout << "No path exists between " << s << " and " << d << endl;
        return;
    }

    list<string> path;
    int curr = dest;

    while (curr != -1) {
        path.push_front(v1[curr]);
        curr = parent[curr].second;
    }
    SetConsoleTextAttribute(h,5);
    cout << "\n\t\t\tShortest path between " << s << " and " << d << " is: \n";
    cout<<"\t\t\t";
    for (auto it = path.begin(); it != path.end(); ++it) {
       
         if (it != path.begin()) {
            cout <<" -> ";
        }
        cout << *it;
    }
    cout << "\n\n";
}


void loadingBar()
{
	// 0 - black background,
	// A - Green Foreground
	// system("color 0A");
    SetConsoleTextAttribute(h,1);

	// Initialize char for printing
	// loading bar
	char a = 177, b = 219;

	printf("\n\n\t\t\tLoading...\n\n");
	printf("\t\t\t");

	// Print initial loading bar
	for (int i = 0; i < 30; i++)
		printf("%c", a);

	// Set the cursor again starting
	// point of loading bar
	printf("\r");
	printf("\t\t\t");

	// Print loading bar progress
	for (int i = 0; i < 30; i++) {
		printf("%c", b);

		// Sleep for 1 second
		Sleep(200);
	}
}

int main() {
    Graph g;

    loadingBar();
    system("cls");
    cout <<"\n\n";
    g.addVertex("Chroy Chongvar");
    g.addVertex("Prek Pnov");
    g.addVertex("Russey Keo");
    g.addVertex("Sen Sok");
    g.addVertex("Por Senchey");
    g.addVertex("Kamboul");
    g.addVertex("Dangkao");
    g.addVertex("Mean Chey");
    g.addVertex("Toul Kouk");
    g.addVertex("Doun Penh");
    g.addVertex("Prampi Makara");
    g.addVertex("Chamkar Mon");
    g.addVertex("Boeng Kengkong");
    g.addVertex("Chbar Ampov");

    g.addEdge("Chroy chongvar", "Russey Keo", 5.9);   
    g.addEdge("Chroy chongvar", "Doun Penh", 2.6);
    g.addEdge("Chroy chongvar", "Prek Pnov", 14.7);
    
    g.addEdge("Prek Pnov","Russey Keo", 11.1);
    g.addEdge("Prek Pnov","Sen Sok", 10);
    g.addEdge("Prek Pnov","Por Senchey", 19.6);
    g.addEdge("Prek Pnov","Kamboul", 23.6);

    g.addEdge("Kamboul", "Por Senchey", 4.3);
    g.addEdge("Kamboul", "Dangkao", 18.4);

    g.addEdge("Dangkao", "Por Senchey", 16.4);
    g.addEdge("Dangkao", "Mean Chey", 6.8);

    g.addEdge("Mean Chey", "Por Senchey", 11.4);
    g.addEdge("Mean Chey", "Sen Sok", 9.6);
    g.addEdge("Mean Chey", "Toul Kouk", 5.7);
    g.addEdge("Mean Chey", "Chamkar Mon", 6);
    g.addEdge("Mean Chey", "Boeng Kengkong", 6.8);
    g.addEdge("Mean Chey", "Chbar Ampov", 18);

    g.addEdge("Chbar Ampov","Boeng Kengkong", 14);

    g.addEdge("Boeng Kengkong", "Chamkar Mon", 0.85);
    g.addEdge("Boeng Kengkong", "Doun Penh", 2.5);

    g.addEdge("Doun Penh", "Chamkar Mon", 2.7);
    g.addEdge("Doun Penh", "Prampi Makara", 1.6);
    g.addEdge("Doun Penh", "Toul Kouk", 3.5);
    g.addEdge("Doun Penh", "Russey Keo", 10.6);

    g.addEdge("Prampi Makara", "Chamkar Mon", 2.8);
    g.addEdge("Prampi Makara", "Toul Kouk", 2.9);
    
    g.addEdge("Toul Kouk", "Russey Keo", 7);
    g.addEdge("Toul Kouk", "Sen Sok", 7.1);

    g.addEdge("Sen Sok", "Por Senchey", 15.4);
    g.addEdge("Sen Sok", "Russey Keo", 9.1);

    string s = "Prek Pnov";
    string d = "Chbar Ampov";

    double shortestDist = g.shortestDistance(s, d);
    SetConsoleTextAttribute(h,3);
    cout << "\n\t\t\tTotal distance of " << s << " and " << d << " is: " << shortestDist << endl;
    g.printAllPaths(s,d);
    cout <<"\n\n";
    return 0;
}