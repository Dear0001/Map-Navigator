#include <iostream>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <climits>
#include <windows.h>

using namespace std;

// Console color handler
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

// List of anime districts (Can be customized to different themes)
vector<string> v1 = {"Chroy Chongvar", "Prek Pnov", "Russey Keo", "Sen Sok", "Por Senchey", "Kamboul", 
                     "Dangkao", "Mean Chey", "Toul Kouk", "Doun Penh", "Prampi Makara", "Chamkar Mon", 
                     "Boeng Kengkong", "Chbar Ampov"};

// Print anime-themed welcome screen
void printWelcomeScreen() {
    SetConsoleTextAttribute(h, 11); // Set color to bright cyan
    cout << R"( 
  _____  _                   _              _                 _             
 |  __ \| |                 | |            | |               | |            
 | |  | | |__   __ _ _ __ __| |_   _  ___  | |_ _ __ __ _ ___| |_ ___  _ __ 
 | |  | | '_ \ / _` | '__/ _` | | | |/ _ \ | __| '__/ _` / __| __/ _ \| '__|
 | |__| | | | | (_| | | | (_| | |_| |  __/ | |_| | | (_| \__ \ || (_) | |   
 |_____/|_| |_|\__,_|_|  \__,_|\__,_|\___|  \__|_|  \__,_|___/\__\___/|_|   
                                                                          
)" << endl;

    SetConsoleTextAttribute(h, 14); // Set color to yellow
    cout << "\nWelcome to the Anime Themed Shortest Path Finder!" << endl;
    cout << "Explore the districts of the city as if you were in your favorite anime!" << endl;
    cout << "Let's find the best route for your favorite characters to meet!" << endl << endl;

    SetConsoleTextAttribute(h, 7); // Reset to default color
}

// A directed graph using adjacency list representation
class Graph {
    map<string, double> vertexMap; // Map to store vertex names and their indices
    vector<list<pair<double, double>>> adj; // Adjacency list representing the graph

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

        for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = it->first;
            double weight = it->second;
            
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;  // Set parent of v as u
            }
        }
    }
    
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

    SetConsoleTextAttribute(h, 5); // Set color to magenta
    cout << "\n\t\t\tShortest path between " << s << " and " << d << " is: \n";
    cout << "\t\t\t";
    for (auto it = path.begin(); it != path.end(); ++it) {
        if (it != path.begin()) {
            SetConsoleTextAttribute(h, 9); // Set color to blue for arrows
            cout <<" -> ";
        }
        SetConsoleTextAttribute(h, 6); // Set color to yellow for locations
        cout << *it;
    }
    cout << "\n\n";
}

int main() {
    Graph g;

    // Print the anime-themed welcome screen
    printWelcomeScreen();

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
    
    char choice;
    do {
        string s, d;
        SetConsoleTextAttribute(h, 11);
        cout << "Enter the source location: ";
        SetConsoleTextAttribute(h, 14);
        getline(cin, s);
        SetConsoleTextAttribute(h, 11);
        cout << "Enter the destination location: ";
        SetConsoleTextAttribute(h, 14);
        getline(cin, d);

        double shortestDist = g.shortestDistance(s, d);
        SetConsoleTextAttribute(h,3);
        cout << "\n\t\t\tTotal distance of " << s << " and " << d << " is: " << shortestDist << endl;
        g.printAllPaths(s, d);
        cout <<"\n\n";

        SetConsoleTextAttribute(h, 13);
        cout << "Do you want to enter another path? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
