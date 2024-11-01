#include <stdio.h>
#include <limits.h>

#define MAXN 205
#define MAXM 4050

int n, m, x, s, t;
int level[MAXN], queue[MAXM], head, tail;
int head_t[MAXM], tail_t[MAXM], next_t[MAXM], to_t[MAXM], capacity_t[MAXM];

void addEdge(int u, int v, int w) {
    to_t[tail_t[u]] = v;
    capacity_t[tail_t[u]] = w;
    next_t[tail_t[u]] = head_t[u];
    head_t[u] = tail_t[u]++;

    to_t[tail_t[v]] = u;
    capacity_t[tail_t[v]] = 0;
    next_t[tail_t[v]] = head_t[v];
    head_t[v] = tail_t[v]++;
}

int bfs() {
    int u, v;
    for (u = 1; u <= n; u++) level[u] = 0;
    level[s] = 1;
    queue[head = tail = 1] = s;

    while (head <= tail) {
        u = queue[head++];
        for (v = head_t[u]; v != -1; v = next_t[v])
            if (capacity_t[v] > 0 && level[to_t[v]] == 0) {
                level[to_t[v]] = level[u] + 1;
                queue[++tail] = to_t[v];
            }
    }
    return level[t] > 0;
}

int dfs(int u, int flow) {
    if (u == t || flow == 0) return flow;
    int totalFlow = 0, currentFlow, v;
    for (v = head_t[u]; v != -1; v = next_t[v])
        if (capacity_t[v] > 0 && level[to_t[v]] == level[u] + 1) {
            currentFlow = dfs(to_t[v], flow - totalFlow < capacity_t[v] ? flow - totalFlow : capacity_t[v]);
            if (currentFlow > 0) {
                capacity_t[v] -= currentFlow;
                capacity_t[v ^ 1] += currentFlow;
                totalFlow += currentFlow;
            }
            if (totalFlow == flow) break;
        }
    return totalFlow;
}

int main() {
    int u, v, w, maxFlow = 0, batches;
    scanf("%d%d%d", &n, &m, &x);
    s = 1, t = n;
    for (int i = 0; i <= n; i++) head_t[i] = tail_t[i] = -1;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
    }
    while (bfs()) maxFlow += dfs(s, INT_MAX);
    if (maxFlow == 0) printf("Orz Ni Jinan Saint Cow!\n");
    else {
        batches = (x + maxFlow - 1) / maxFlow;
        printf("%d %d\n", maxFlow, batches);
    }
    return 0;
}