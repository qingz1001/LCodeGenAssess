#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 200005

int n, m;
int head[MAX_N], nxt[MAX_M * 2], to[MAX_M * 2], cnt;
int deg[MAX_N];

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

long long count_triangles() {
    long long res = 0;
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (v > u) {
                for (int j = head[v]; j; j = nxt[j]) {
                    int w = to[j];
                    if (w > v) {
                        for (int k = head[w]; k; k = nxt[k]) {
                            if (to[k] == u) {
                                res++;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
        deg[u]++;
        deg[v]++;
    }
    
    printf("%lld\n", count_triangles());
    
    return 0;
}