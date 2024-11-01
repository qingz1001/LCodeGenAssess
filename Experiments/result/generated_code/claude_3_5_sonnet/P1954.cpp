#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 2005
#define MAXM 10005

int n, m;
int k[MAXN];
int in[MAXN], out[MAXN];
int queue[MAXN], head, tail;
int order[MAXN], cnt;
int earliest[MAXN];
bool graph[MAXN][MAXN];

void topological_sort() {
    head = tail = cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            queue[tail++] = i;
        }
    }
    
    while (head < tail) {
        int u = queue[head++];
        order[cnt++] = u;
        for (int v = 1; v <= n; v++) {
            if (graph[u][v]) {
                if (--in[v] == 0) {
                    queue[tail++] = v;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &k[i]);
    }
    
    memset(graph, 0, sizeof(graph));
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (!graph[a][b]) {
            graph[a][b] = true;
            in[b]++;
            out[a]++;
        }
    }
    
    topological_sort();
    
    for (int i = 0; i < n; i++) {
        printf("%d ", order[i]);
    }
    printf("\n");
    
    memset(earliest, 0, sizeof(earliest));
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        earliest[u] = n;
        for (int v = 1; v <= n; v++) {
            if (graph[u][v]) {
                earliest[u] = (earliest[u] < earliest[v] - 1) ? earliest[u] : (earliest[v] - 1);
            }
        }
        earliest[u] = (earliest[u] < k[u]) ? earliest[u] : k[u];
    }
    
    for (int i = 1; i <= n; i++) {
        printf("%d ", earliest[i]);
    }
    printf("\n");
    
    return 0;
}