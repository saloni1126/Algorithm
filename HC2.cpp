#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>

using namespace std;

class Graph {
public:
    Graph(int numVertices) : numVertices(numVertices) {
        adjList.resize(numVertices);
    }

    void addEdge(char src, char dest, int cost) {
        int srcIndex = src - 'A';
        int destIndex = dest - 'A';
        adjList[srcIndex].push_back(make_pair(dest, cost));
        adjList[destIndex].push_back(make_pair(src, cost)); // For an undirected graph
    }

    bool hillClimbing(char start, char goal, unordered_map<char, char>& parent) {
        int startIndex = start - 'A';
        int goalIndex = goal - 'A';

        priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq; // Min-heap

        unordered_map<char, int> heuristic; // Heuristic values
        for (int i = 0; i < numVertices; i++) {
            heuristic[char('A' + i)] = estimateHeuristic(char('A' + i), goal);
        }

        vector<bool> visited(numVertices, false);
        visited[startIndex] = true;
        parent[start] = '\0';

        pq.push(make_pair(heuristic[start], start));

        while (!pq.empty()) {
            char current = pq.top().second;
            pq.pop();

            if (current == goal) {
                return true; // Found a path to the goal
            }

            for (pair<char, int> neighbor : adjList[current - 'A']) {
                char next = neighbor.first;
                int cost = neighbor.second;

                if (!visited[next - 'A']) {
                    visited[next - 'A'] = true;
                    parent[next] = current;
                    pq.push(make_pair(heuristic[next] + cost, next));
                }
            }
        }

        return false; // No path to the goal
    }

    int estimateHeuristic(char current, char goal) {
        // You can implement your heuristic function here.
        // This example uses a simple Manhattan distance heuristic.
        return abs(current - goal);
    }
private:
    int numVertices;
    vector<vector<pair<char, int>>> adjList;
};

int main() {
    Graph graph(26);

    graph.addEdge('S', 'A', 1);
    graph.addEdge('S', 'B', 3);
    graph.addEdge('A', 'F', 5);
    graph.addEdge('B', 'C', 2);
    graph.addEdge('B', 'D', 4);
    graph.addEdge('C', 'E', 1);
    graph.addEdge('D', 'F', 3);
    graph.addEdge('E', 'F', 2);

    char start = 'S';
    char goal = 'F';

    unordered_map<char, char> parent;
    for (char c = 'A'; c <= 'Z'; c++) {
        parent[c] = '\0';
    }

    if (graph.hillClimbing(start, goal, parent)) {
        cout << "Path found!" << endl;
        cout << "Path: ";
        while (goal != start) {
            cout << goal << " <- ";
            goal = parent[goal];
        }
        cout << start << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
