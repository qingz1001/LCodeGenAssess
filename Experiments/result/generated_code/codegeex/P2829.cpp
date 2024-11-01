#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 5001;
const int INF = 1e9;

struct Edge {
    int u, v, w;
};

vector<Edge> edges;
vector<int> graph[MAXN];
int dist[MAXN][2];
bool visited[MAXN][2];
int n, m, k;

void addEdge(int u, int v, int w) {
    edges.push_back({u, v, w});
    graph[u].push_back(edges.size() - 1);
    edges.push_back({v, u, w});
    graph[v].push_back(edges.size() - 1);
}

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    fill(&dist[0][0], &dist[MAXN - 1][2], INF);
    fill(&visited[0][0], &visited[MAXN - 1][2], false);
    dist[1][0] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u][0]) continue;
        visited[u][0] = true;

        for (int i : graph[u]) {
            int v = edges[i].v;
            int w = edges[i].w;
            if (!visited[v][0] && dist[u][0] + w < dist[v][0]) {
                dist[v][0] = dist[u][0] + w;
                pq.push({dist[v][0], v});
            }
        }
    }
}

void dijkstra2() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    fill(&dist[0][1], &dist[MAXN - 1][2], INF);
    fill(&visited[0][1], &visited[MAXN - 1][2], false);
    dist[1][1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u][1]) continue;
        visited[u][1] = true;

        for (int i : graph[u]) {
            int v = edges[i].v;
            int w = edges[i].w;
            if (!visited[v][1] && dist[u][1] + w < dist[v][1]) {
                dist[v][1] = dist[u][1] + w;
                pq.push({dist[v][1], v});
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    dijkstra();
    dijkstra2();

    int minDist = dist[n][0];
    int secondMinDist = INF;
    for (int i : graph[n]) {
        int u = edges[i].u;
        if (u != 1 && (int)graph[u].size() < k) {
            secondMinDist = min(secondMinDist, dist[u][1] + edges[i].w);
        }
    }

    for (int i : graph[n]) {
        int u = edges[i].u;
        if (u != 1 && (int)graph[u].size() >= k) {
            secondMinDist = min(secondMinDist, dist[u][0] + edges[i].w);
        }
    }

    if (secondMinDist == INF || secondMinDist == minDist) {
        printf("-1\n");
    } else {
        printf("%d\n", secondMinDist);
    }

    return 0;
}