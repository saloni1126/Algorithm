#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>
#include <climits> // Include this header for INT_MAX

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

    bool beamSearch(char start, char goal, unordered_map<char, char>& parent, int beamWidth) {
        int startIndex = start - 'A';
        int goalIndex = goal - 'A';

        struct BeamNode {
            char node;
            int cost;

            bool operator<(const BeamNode& other) const {
                return cost > other.cost; // Min-heap based on cost
            }
        };

        priority_queue<BeamNode> beamQueue;
        vector<int> costSoFar(numVertices, INT_MAX);
        vector<bool> visited(numVertices, false);
        visited[startIndex] = true;
        parent[start] = '\0';

        beamQueue.push({start, 0});
        int candidatesExplored = 0;

        while (!beamQueue.empty() && candidatesExplored < beamWidth) {
            char current = beamQueue.top().node;
            int currentCost = beamQueue.top().cost;
            beamQueue.pop();

            if (current == goal) {
                return true; // Found a path to the goal
            }

            for (pair<char, int> neighbor : adjList[current - 'A']) {
                char next = neighbor.first;
                int cost = neighbor.second;

                if (!visited[next - 'A'] || costSoFar[next - 'A'] > currentCost + cost) {
                    visited[next - 'A'] = true;
                    parent[next] = current;
                    costSoFar[next - 'A'] = currentCost + cost;
                    beamQueue.push({next, costSoFar[next - 'A']});
                }
            }

            candidatesExplored++;
        }

        return false; // No path to the goal
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

    int beamWidth = 7; // Adjust the beam width as needed

    if (graph.beamSearch(start, goal, parent, beamWidth)) {
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
