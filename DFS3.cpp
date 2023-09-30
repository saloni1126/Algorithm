#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <climits>

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
        adjList[destIndex].push_back(make_pair(src, cost)); 
    }

    bool dfs(char start, char goal, unordered_map<char, char>& parent) {
        int startIndex = start - 'A';
        int goalIndex = goal - 'A';

        vector<bool> visited(numVertices, false);
        stack<char> s;

        s.push(start);

        while (!s.empty()) {
            char current = s.top();
            s.pop();

            if (current == goal) {
                return true; 
            }

            if (visited[current - 'A']) {
                continue; 
            }

            visited[current - 'A'] = true;

            for (const auto& edge : adjList[current - 'A']) {
                char neighbor = edge.first;

                if (!visited[neighbor - 'A']) {
                    parent[neighbor] = current;
                    s.push(neighbor);
                }
            }
        }

        return false; 
    }

private:
    int numVertices;
    vector<vector<pair<char, int>>> adjList;
};

int main() {
    Graph graph(26);

    graph.addEdge('S', 'A', 4);
    graph.addEdge('S', 'B', 6);
    graph.addEdge('S', 'C', 3);
    graph.addEdge('A', 'D', 8);
    graph.addEdge('A', 'E', 7);
    graph.addEdge('B', 'F', 4);
    graph.addEdge('B', 'G', 7);
    graph.addEdge('C', 'H', 9);
    graph.addEdge('C', 'J', 8);
    graph.addEdge('G', 'H', 2);
    graph.addEdge('D', 'K', 2);
    graph.addEdge('E', 'M', 5);
    graph.addEdge('F', 'O', 3);
    graph.addEdge('G', 'O', 5);
    graph.addEdge('K', 'M', 1);
    graph.addEdge('M', 'O', 4);
    graph.addEdge('J', 'R', 5);
    graph.addEdge('J', 'T', 4);
    graph.addEdge('R', 'T', 3);

    char start = 'S';
    char goal = 'G';

    unordered_map<char, char> parent;
    for (char c = 'A'; c <= 'Z'; c++) {
        parent[c] = '\0';
    }

    if (graph.dfs(start, goal, parent)) {
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
