#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define MAXM 100005

typedef long long ll;

struct Edge {
    int to;
    ll weight;
    int next;
} edges[MAXM * 2];

int head[MAXN], tot;
int n, m;
ll dp[MAXN][61];

void addEdge(int u, int v, ll w) {
    edges[tot].to = v;
    edges[tot].weight = w;
    edges[tot].next = head[u];
    head[u] = tot++;
}

int main() {
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    
    for (int i = 60; i >= 0; i--) {
        for (int j = 1; j <= n; j++) {
            dp[j][i] = -1;
        }
        dp[n][i] = 0;
        
        int changed = 1;
        while (changed) {
            changed = 0;
            for (int u = 1; u <= n; u++) {
                if (dp[u][i] == -1) continue;
                for (int e = head[u]; e != -1; e = edges[e].next) {
                    int v = edges[e].to;
                    ll w = edges[e].weight;
                    ll newValue = dp[u][i];
                    if ((w >> i) & 1) newValue |= (1LL << i);
                    if (newValue > dp[v][i]) {
                        dp[v][i] = newValue;
                        changed = 1;
                    }
                }
            }
        }
    }
    
    printf("%lld\n", dp[1][60]);
    
    return 0;
}