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

struct NodeInfo {
    int g_value;
    int h_value;
};


int heuristic(const string& current, const string& goal) {
    return abs(current[0] - goal[0]);
}

vector<string> aoStarSearch(const unordered_map<string, vector<Edge>>& graph, const string& start, const string& goal) {
    unordered_map<string, bool> visited;
    unordered_map<string, string> parent;
    unordered_map<string, NodeInfo> node_info;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> open_list;

    open_list.push({0, start});
    visited[start] = true;
    node_info[start] = {0, heuristic(start, goal)};

    while (!open_list.empty()) {
        string node = open_list.top().second;
        open_list.pop();

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

            int tentative_g_value = node_info[node].g_value + weight;

            if (!visited[neighbor] || tentative_g_value < node_info[neighbor].g_value) {
                visited[neighbor] = true;
                parent[neighbor] = node;
                node_info[neighbor] = {tentative_g_value, heuristic(neighbor, goal)};
                int f_value = tentative_g_value + node_info[neighbor].h_value;
                open_list.push({f_value, neighbor});
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

    vector<string> path = aoStarSearch(graph, start, goal);

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
