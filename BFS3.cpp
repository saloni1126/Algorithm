#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
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

    bool bfs(char start, char goal, unordered_map<char, char>& parent) {
        int startIndex = start - 'A';
        int goalIndex = goal - 'A';

        vector<bool> visited(numVertices, false);
        priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq; 

        pq.push(make_pair(0, start));

        while (!pq.empty()) {
            char current = pq.top().second;
            int currentCost = pq.top().first;
            pq.pop();

            if (current == goal) {
                return true; 
            }

            if (visited[current - 'A']) {
                continue; 
            }

            visited[current - 'A'] = true;

            for (const auto& edge : adjList[current - 'A']) {
                char neighbor = edge.first;
                int edgeCost = edge.second;

                if (!visited[neighbor - 'A']) {
                    int newCost = currentCost + edgeCost;
                    pq.push(make_pair(newCost + heuristic(neighbor, goal), neighbor));
                    parent[neighbor] = current;
                }
            }
        }

        return false; 
    }

private:
    int numVertices;
    vector<vector<pair<char, int>>> adjList;

   
    int heuristic(char current, char goal) {
        
        int currentX = current - 'A';
        int goalX = goal - 'A';
        return abs(currentX - goalX);
    }
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

