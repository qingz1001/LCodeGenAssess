#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <vector>
#define inf 0x3f3f3f3f
using namespace std;

struct Edge {
    int to, next, w;
} edges[2501];

int head[51], dist[51], vis[51];
int n, m, s, t, k, a, T, min_blood = inf;
int monster_rooms[5];
int cycle_length[5] = {0, 1, 2, 3, 4};

void add_edge(int u, int v, int w) {
    edges[m].to = v;
    edges[m].w = w;
    edges[m].next = head[u];
    head[u] = m++;
}

void spfa() {
    memset(dist, inf, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    vis[s] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;

        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            int w = edges[i].w;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &k);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    scanf("%d", &a);

    for (int i = 0; i < a; i++) {
        scanf("%d", &T);
        for (int j = 0; j < T; j++) {
            scanf("%d", &monster_rooms[j]);
        }
        cycle_length[T]++;
    }

    for (int i = 0; i < cycle_length[T]; i++) {
        spfa();
        if (dist[t] < inf) {
            min_blood = min(min_blood, dist[t]);
        }
        for (int j = 0; j < T; j++) {
            for (int l = head[monster_rooms[j]]; l != -1; l = edges[l].next) {
                int v = edges[l].to;
                int w = edges[l].w;
                edges[l].w = inf;
                edges[l].next = head[v];
                add_edge(v, monster_rooms[j], w);
            }
        }
    }

    if (min_blood >= inf) {
        printf("IMP0SSBLE!!");
    } else {
        printf("%d", min_blood);
    }

    return 0;
}