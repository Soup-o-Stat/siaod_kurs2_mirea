#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <limits>
#include <algorithm>
using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    char from, to;
    int weight;
};

class Graph {
    map<char, vector<pair<char, int>>> adjList;

public:
    void addEdge(char u, char v, int weight) {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight);
    }

    const map<char, vector<pair<char, int>>>& getAdjList() const {
        return adjList;
    }

    pair<vector<char>, int> dijkstra(char start, char end, set<pair<char, char>>& blockedEdges) const {
        map<char, int> dist;
        map<char, char> prev;
        set<char> visited;

        for (auto& pair : adjList) {
            dist[pair.first] = INF;
        }
        dist[start] = 0;

        auto cmp = [&dist](char left, char right) { return dist[left] > dist[right]; };
        priority_queue<char, vector<char>, decltype(cmp)> pq(cmp);
        pq.push(start);

        while (!pq.empty()) {
            char current = pq.top();
            pq.pop();
            if (visited.count(current)) continue;

            visited.insert(current);

            for (auto& pair : adjList.at(current)) {
                char neighbor = pair.first;
                int weight = pair.second;

                if (blockedEdges.count({current, neighbor}) || blockedEdges.count({neighbor, current})) {
                    continue;
                }

                int newDist = dist[current] + weight;
                if (newDist < dist[neighbor]) {
                    dist[neighbor] = newDist;
                    prev[neighbor] = current;
                    pq.push(neighbor);
                }
            }
        }

        vector<char> path;
        int totalWeight = dist[end];
        for (char at = end; at != 0; at = prev[at])
            path.push_back(at);
        reverse(path.begin(), path.end());

        return (path.front() == start) ? make_pair(path, totalWeight) : make_pair(vector<char>(), INF);
    }

    vector<pair<vector<char>, int>> yenKShortestPaths(char start, char end, int k) {
        vector<pair<vector<char>, int>> shortestPaths;
        set<pair<vector<char>, int>> candidates;

        set<pair<char, char>> blockedEdges;
        auto basePath = dijkstra(start, end, blockedEdges);
        if (basePath.first.empty()) return shortestPaths;

        shortestPaths.push_back(basePath);
        blockedEdges.clear();

        for (int i = 1; i < k; ++i) {
            const auto& lastPath = shortestPaths.back().first;

            for (size_t j = 0; j < lastPath.size() - 1; ++j) {
                char spurNode = lastPath[j];

                Graph tempGraph = *this;
                set<pair<char, char>> tempBlockedEdges = blockedEdges;

                for (size_t pathIdx = 0; pathIdx <= j; ++pathIdx) {
                    char u = lastPath[pathIdx], v = lastPath[pathIdx + 1];
                    tempGraph.removeEdge(u, v);
                    tempBlockedEdges.insert({u, v});
                }

                auto spurPath = tempGraph.dijkstra(spurNode, end, tempBlockedEdges);
                if (spurPath.first.empty()) continue;

                vector<char> totalPath(lastPath.begin(), lastPath.begin() + j);
                totalPath.insert(totalPath.end(), spurPath.first.begin(), spurPath.first.end());
                int totalWeight = 0;

                for (size_t idx = 0; idx < totalPath.size() - 1; ++idx) {
                    char u = totalPath[idx], v = totalPath[idx + 1];
                    for (auto& edge : adjList.at(u)) {
                        if (edge.first == v) {
                            totalWeight += edge.second;
                            break;
                        }
                    }
                }

                candidates.insert(make_pair(totalPath, totalWeight));
            }

            if (candidates.empty()) break;

            shortestPaths.push_back(*candidates.begin());
            candidates.erase(candidates.begin());
        }

        return shortestPaths;
    }

    void removeEdge(char u, char v) {
        adjList[u].erase(
            remove_if(adjList[u].begin(), adjList[u].end(), [v](const auto& edge) { return edge.first == v; }),
            adjList[u].end());
        adjList[v].erase(
            remove_if(adjList[v].begin(), adjList[v].end(), [u](const auto& edge) { return edge.first == u; }),
            adjList[v].end());
    }
};

int main() {
    Graph graph;

    int edgesCount;
    cout << "Enter the number of edges: ";
    cin >> edgesCount;

    cout << "Enter the edges in the format (from, to, weight):" << endl;
    for (int i = 0; i < edgesCount; ++i) {
        char u, v;
        int weight;
        cin >> u >> v >> weight;
        graph.addEdge(u, v, weight);
    }

    char start, end;
    cout << "Enter the start and end vertices: ";
    cin >> start >> end;

    int k;
    cout << "Enter the number of shortest paths to find: ";
    cin >> k;

    auto paths = graph.yenKShortestPaths(start, end, k);

    cout << "The shortest paths are:" << endl;
    for (size_t i = 0; i < paths.size(); ++i) {
        cout << "Path " << i + 1 << "(Length: " << paths[i].second << "): ";
        for (char node : paths[i].first) {
            cout << node << " ";
        }
        cout << endl;
    }
    return 0;
}
