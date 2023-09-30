#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(int numVertices) : numVertices(numVertices) {
        adjList.resize(numVertices);
    }

    void addEdge(char src, char dest) {
        int srcIndex = src - 'A';
        int destIndex = dest - 'A';
        adjList[srcIndex].push_back(dest);
        adjList[destIndex].push_back(src); 
    }

    bool bfs(char start, char goal, unordered_map<char, char>& parent) {
        int startIndex = start - 'A';
        int goalIndex = goal - 'A';

        vector<bool> visited(numVertices, false);
        queue<char> q;

        visited[startIndex] = true;
        q.push(start);

        while (!q.empty()) {
            char current = q.front();
            q.pop();

            if (current == goal) {
                return true; 
            }

            for (char neighbor : adjList[current - 'A']) {
                if (!visited[neighbor - 'A']) {
                    visited[neighbor - 'A'] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }

        return false; 
    }
private:
    int numVertices;
    vector<vector<char>> adjList;
};

int main() {
    Graph graph(26);

    graph.addEdge('S', 'A');
    graph.addEdge('S', 'B');
    graph.addEdge('A', 'F');
    graph.addEdge('B', 'C');
    graph.addEdge('B', 'D');
    graph.addEdge('C', 'E');
    graph.addEdge('D', 'F');
    graph.addEdge('E', 'F');

    char start = 'S';
    char goal = 'F';

    unordered_map<char, char> parent;
    for (char c = 'A'; c <= 'Z'; c++) {
        parent[c] = '\0';
    }

    if (graph.bfs(start, goal, parent)) {
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
