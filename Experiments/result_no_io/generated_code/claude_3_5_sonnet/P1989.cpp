#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], deg[MAXN];
int n, m, cnt;

void add_edge(int u, int v) {
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt++;
}

long long count_triangles() {
    long long ans = 0;
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; ~i; i = nxt[i]) {
            int v = to[i];
            if (v > u) {
                for (int j = head[v]; ~j; j = nxt[j]) {
                    int w = to[j];
                    if (w > v) {
                        for (int k = head[w]; ~k; k = nxt[k]) {
                            if (to[k] == u) {
                                ans++;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return ans;
}

int main() {
    scanf("%d %d", &n, &m);
    
    memset(head, -1, sizeof(head));
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
        deg[u]++;
        deg[v]++;
    }
    
    printf("%lld\n", count_triangles());
    
    return 0;
}