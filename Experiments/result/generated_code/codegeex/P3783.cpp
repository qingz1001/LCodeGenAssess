#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int MAXN = 50010;
const int MAXM = 50010;
const int MAXK = 200010;

struct Edge {
    int to, weight, len;
};

vector<Edge> graph[MAXN];
int dist[MAXN];
bool inQueue[MAXN];
int T, n, m, k;

void init() {
    for (int i = 1; i <= n; i++) {
        graph[i].clear();
        dist[i] = INT_MAX;
        inQueue[i] = false;
    }
}

void addEdge(int u, int v, int w, int l) {
    graph[u].push_back({v, w, l});
}

void dijkstra(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist[u]) continue;
        for (auto& edge : graph[u]) {
            int v = edge.to;
            int w = edge.weight;
            int l = edge.len;
            if (dist[u] + w + l < dist[v]) {
                dist[v] = dist[u] + w + l;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        init();
        for (int i = 0; i < m; i++) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            addEdge(a, b, c, 0);
        }
        for (int i = 1; i < k; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            addEdge(u, v, 0, w);
        }
        dijkstra(1);
        for (int i = 2; i <= n; i++) {
            printf("%d\n", dist[i]);
        }
    }
    return 0;
}