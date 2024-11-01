#include <stdio.h>
#include <string.h>

#define MAXN 3005
#define MAXM 8005

int n, p, r, a, b, c, d, minn = 0x3f3f3f3f;
int low[MAXN], dfn[MAXN], flag[MAXN], stack[MAXN], vis[MAXN], sum[MAXN], num[MAXN];
int head[MAXN], to[MAXM], next[MAXM], tot;

void add(int x, int y) {
    to[tot] = y;
    next[tot] = head[x];
    head[x] = tot++;
}

void tarjan(int x) {
    low[x] = dfn[x] = ++tot;
    stack[++c] = x;
    vis[x] = 1;
    for (int i = head[x]; i != -1; i = next[i]) {
        int y = to[i];
        if (!dfn[y]) {
            tarjan(y);
            low[x] = (low[x] < low[y]) ? low[x] : low[y];
        } else if (vis[y]) {
            low[x] = (low[x] < dfn[y]) ? low[x] : dfn[y];
        }
    }
    if (low[x] == dfn[x]) {
        d++;
        int k;
        do {
            k = stack[c--];
            vis[k] = 0;
            flag[k] = d;
            sum[d] += num[k];
            num[d] = (num[d] > minn) ? num[d] : minn;
        } while (k != x);
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= p; i++) {
        scanf("%d%d", &a, &b);
        num[a] = b;
        minn = (minn > b) ? b : minn;
    }
    scanf("%d", &r);
    for (int i = 1; i <= r; i++) {
        scanf("%d%d", &a, &b);
        add(a, b);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tot = 0;
            tarjan(i);
        }
    }
    for (int i = 1; i <= d; i++) {
        if (num[i] == 0) {
            printf("NO\n%d", i);
            return 0;
        }
    }
    printf("YES\n");
    int ans = 0;
    for (int i = 1; i <= d; i++) {
        ans += num[i];
    }
    printf("%d", ans);
    return 0;
}