#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50005
#define MAXM 100005

typedef long long ll;

struct Edge {
    int to;
    ll weight;
    struct Edge *next;
};

struct Edge *head[MAXN];
ll dist[MAXN];
int prev[MAXN];
int n, m;

void add_edge(int from, int to, ll weight) {
    struct Edge *new_edge = (struct Edge *)malloc(sizeof(struct Edge));
    new_edge->to = to;
    new_edge->weight = weight;
    new_edge->next = head[from];
    head[from] = new_edge;
}

void dijkstra() {
    for (int i = 1; i <= n; i++) {
        dist[i] = LLONG_MAX;
    }
    dist[1] = 0;
    while (1) {
        int u = -1;
        ll min_dist = LLONG_MAX;
        for (int i = 1; i <= n; i++) {
            if (dist[i] < min_dist) {
                u = i;
                min_dist = dist[i];
            }
        }
        if (u == -1 || u == n) {
            break;
        }
        struct Edge *edge = head[u];
        while (edge != NULL) {
            int v = edge->to;
            ll weight = edge->weight;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
            edge = edge->next;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        ll v;
        scanf("%lld", &v);
        for (int j = 1; j < i; j++) {
            if (v != 0) {
                add_edge(i, j, (ll)(i - j) * v);
                add_edge(j, i, (ll)(j - i) * v);
            }
        }
    }
    for (int i = 0; i < m; i++) {
        int s_l, s_r, t_l, t_r;
        ll w;
        scanf("%d %d %d %d %lld", &s_l, &s_r, &t_l, &t_r, &w);
        for (int s = s_l; s <= s_r; s++) {
            for (int t = t_l; t <= t_r; t++) {
                add_edge(s, t, w);
            }
        }
    }
    dijkstra();
    if (dist[n] == LLONG_MAX) {
        printf("-1\n");
    } else {
        printf("%lld\n", dist[n]);
        if (prev[n] == 0) {
            printf("0\n");
        } else {
            int count = 0;
            for (int i = n; i != 0; i = prev[i]) {
                count++;
            }
            printf("%d\n", count);
            for (int i = n; i != 0; i = prev[i]) {
                printf("%d ", i);
            }
            printf("\n");
        }
    }
    return 0;
}