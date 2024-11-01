#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int n, m, s, t, tot = 1;
int head[1005], cur[1005], deep[1005];
struct edge {
    int to, next, flow;
} e[1000005];

void add(int x, int y, int w) {
    e[++tot].to = y;
    e[tot].flow = w;
    e[tot].next = head[x];
    head[x] = tot;
    e[++tot].to = x;
    e[tot].flow = 0;
    e[tot].next = head[y];
    head[y] = tot;
}

int bfs() {
    memset(deep, 0, sizeof(deep));
    memcpy(cur, head, sizeof(head));
    deep[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i; i = e[i].next) {
            if (e[i].flow && !deep[e[i].to]) {
                deep[e[i].to] = deep[x] + 1;
                q.push(e[i].to);
            }
        }
    }
    return deep[t];
}

int dfs(int x, int flow) {
    if (x == t) return flow;
    for (int i = cur[x]; i; i = e[i].next) {
        cur[x] = i;
        if (e[i].flow && deep[e[i].to] == deep[x] + 1) {
            int f = dfs(e[i].to, min(flow, e[i].flow));
            if (f) {
                e[i].flow -= f;
                e[i^1].flow += f;
                return f;
            }
        }
    }
    return 0;
}

int dinic() {
    int ans = 0;
    while (bfs()) {
        while (int d = dfs(s, 0x3f3f3f3f)) ans += d;
    }
    return ans;
}

int main() {
    scanf("%d%d", &m, &n);
    s = 0, t = 2 * m * n + 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == 1 && j == 1) add(s, (i - 1) * n + j, 1);
            if (i == m && j == n) add((i - 1) * n + j, t, 1);
            if (i > 1) add((i - 1) * n + j, (i - 2) * n + j, 0x3f3f3f3f);
            if (i < m) add((i - 1) * n + j, i * n + j, 0x3f3f3f3f);
            if (j > 1) add((i - 1) * n + j, (i - 1) * n + j - 1, 0x3f3f3f3f);
            if (j < n) add((i - 1) * n + j, (i - 1) * n + j + 1, 0x3f3f3f3f);
        }
    }
    printf("%d", dinic());
    return 0;
}