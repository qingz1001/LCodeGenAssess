#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 50;
const int INF = 1e9;

int n, m, k;
int r[MAXN], d[MAXN];
bool has_castle[MAXN];
int dist[MAXN];
bool visited[MAXN];
vector<pair<int, int>> adj[MAXN];

void dijkstra(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    fill(dist, dist + n, INF);
    fill(visited, visited + n, false);
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &r[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &d[i]);
    }
    for (int i = 0; i < m; ++i) {
        int castle;
        scanf("%d", &castle);
        has_castle[castle] = true;
    }

    for (int i = 0; i < n; ++i) {
        adj[i].push_back({r[i], d[i]});
        adj[r[i]].push_back({i, d[i]});
    }

    int max_dist = 0;
    for (int i = 0; i < n; ++i) {
        if (!has_castle[i]) {
            dijkstra(i);
            int min_dist = INF;
            for (int j = 0; j < n; ++j) {
                if (has_castle[j]) {
                    min_dist = min(min_dist, dist[j]);
                }
            }
            max_dist = max(max_dist, min_dist);
        }
    }

    int remaining_cities = n - m;
    int additional_castles = min(k, remaining_cities);
    printf("%d\n", max_dist + additional_castles);

    return 0;
}