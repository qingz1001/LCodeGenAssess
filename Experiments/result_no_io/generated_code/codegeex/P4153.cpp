#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 150005
#define MAXM 300005
#define MAXK 100005

int n, m, s, t, k;
int head[MAXN], to[MAXM], next[MAXM], weight[MAXM], tot;
int maxflow, gap[MAXN], dis[MAXN], cur[MAXN], que[MAXN], l, r;
int vis[MAXN], cnt[MAXN], ans[MAXK], num;
int que2[MAXK], l2, r2;

void add(int x, int y, int z) {
    to[tot] = y;
    weight[tot] = z;
    next[tot] = head[x];
    head[x] = tot++;
}

void bfs() {
    memset(dis, -1, sizeof(dis));
    memset(gap, 0, sizeof(gap));
    l = r = 0;
    que[r++] = t;
    dis[t] = 0;
    gap[0]++;
    while (l < r) {
        int x = que[l++];
        for (int i = head[x]; i != -1; i = next[i]) {
            int y = to[i];
            if (dis[y] == -1) {
                que[r++] = y;
                dis[y] = dis[x] + 1;
                gap[dis[y]]++;
            }
        }
    }
}

int dfs(int x, int flow) {
    if (x == t) {
        maxflow += flow;
        return flow;
    }
    int used = 0;
    for (int &i = cur[x]; i != -1; i = next[i]) {
        int y = to[i], z = weight[i];
        if (z > 0 && dis[x] == dis[y] + 1) {
            int w = dfs(y, min(flow - used, z));
            if (w > 0) {
                weight[i] -= w;
                weight[i ^ 1] += w;
                used += w;
            }
            if (used == flow) {
                return used;
            }
        }
    }
    cur[x] = head[x];
    if (--gap[dis[x]] == 0) {
        dis[s] = n;
    }
    gap[++dis[x]]++;
    return used;
}

void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
    maxflow = 0;
}

void Dinic() {
    bfs();
    while (dis[s] < n) {
        memcpy(cur, head, sizeof(cur));
        dfs(s, 0x7fffffff);
    }
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &k);
    init();
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        add(y, x, 0);
    }
    Dinic();
    for (int i = 0; i < tot; i += 2) {
        if (weight[i] == 0) {
            cnt[i / 2]++;
        }
    }
    for (int i = 0; i < tot; i += 2) {
        if (cnt[i / 2] < k) {
            num++;
            ans[num] = weight[i ^ 1];
            que2[r2++] = num;
        }
    }
    if (num < k) {
        printf("%d\n-1\n", num);
    } else {
        for (int i = 0; i < k; i++) {
            printf("%d\n", ans[que2[i]]);
        }
    }
    return 0;
}