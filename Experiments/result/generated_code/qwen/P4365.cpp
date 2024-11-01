#include <stdio.h>
#include <stdlib.h>

#define MOD 64123

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[100010];
int head[100010], edge_cnt;
int n, k, W;
int d[100010];

void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void dfs(int u, int fa, int depth, int *cnt, int *sum) {
    cnt[depth]++;
    sum[depth] += d[u];
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].to;
        if (v == fa) continue;
        dfs(v, u, depth + 1, cnt, sum);
    }
}

int main() {
    scanf("%d %d %d", &n, &k, &W);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }

    int cnt[n + 10], sum[n + 10];
    memset(cnt, 0, sizeof(cnt));
    memset(sum, 0, sizeof(sum));

    dfs(1, -1, 0, cnt, sum);

    long long ans = 0;
    for (int i = k; i <= n; i++) {
        ans += (long long)cnt[i] * sum[i];
        ans %= MOD;
    }

    printf("%lld\n", ans);

    return 0;
}