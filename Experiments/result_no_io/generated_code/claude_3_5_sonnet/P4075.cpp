#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 100005

typedef long long ll;

int n, m;
char s[MAXN], t[MAXM];
int head[MAXN], ecnt;
int f[MAXN][30], dep[MAXN];
ll ans;

struct Edge {
    int to, next;
} edge[MAXN * 2];

void addEdge(int u, int v) {
    edge[++ecnt] = (struct Edge){v, head[u]};
    head[u] = ecnt;
    edge[++ecnt] = (struct Edge){u, head[v]};
    head[v] = ecnt;
}

void dfs(int u, int fa) {
    for (int i = 0; i < 26; i++) {
        f[u][i] = f[fa][i];
    }
    f[u][s[u] - 'A'] = dep[u];
    
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

int main() {
    int C;
    scanf("%d", &C);
    
    while (C--) {
        scanf("%d%d", &n, &m);
        scanf("%s", s + 1);
        
        memset(head, 0, sizeof(head));
        ecnt = 0;
        
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            addEdge(u, v);
        }
        
        scanf("%s", t + 1);
        
        memset(f, -1, sizeof(f));
        dep[1] = 1;
        dfs(1, 0);
        
        ans = 0;
        for (int i = 1; i <= n; i++) {
            int cur = i, len = 0;
            while (cur && len < m) {
                int c = t[len + 1] - 'A';
                if (f[cur][c] == -1) break;
                len++;
                cur = f[cur][c];
            }
            if (len == m) {
                ans += n - cur + 1;
            }
        }
        
        printf("%lld\n", ans);
    }
    
    return 0;
}