#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

struct Edge {
    string node;
    int weight;
};

vector<string> oracleSearch(const unordered_map<string, vector<Edge>>& graph, const string& start, const string& goal) {
    unordered_map<string, bool> visited;
    unordered_map<string, string> parent;
    unordered_map<string, int> g_values; 
    queue<string> q;

    q.push(start);
    visited[start] = true;
    g_values[start] = 0;

    while (!q.empty()) {
        string node = q.front();
        q.pop();

        if (node == goal) {
            vector<string> path;
            while (node != start) {
                path.push_back(node);
                node = parent[node];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (const Edge& edge : graph.at(node)) {
            string neighbor = edge.node;
            int weight = edge.weight;

            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
                parent[neighbor] = node;
                g_values[neighbor] = g_values[node] + weight;
            }
        }
    }

    return {};
}

int main() {
    unordered_map<string, vector<Edge>> graph;
    graph["S"] = {{"A", 1}, {"D", 5}};
    graph["A"] = {{"B", 3}};
    graph["B"] = {{"C", 1}, {"G", 1}};
    graph["C"] = {{"G", 1}};
    graph["D"] = {{"G", 1}};

    string start = "S";
    string goal = "G";

    vector<string> path = oracleSearch(graph, start, goal);

    if (!path.empty()) {
        cout << "Path from " << start << " to " << goal << ": ";
        for (const string& node : path) {
            cout << node << " -> ";
        }
        cout << goal << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
