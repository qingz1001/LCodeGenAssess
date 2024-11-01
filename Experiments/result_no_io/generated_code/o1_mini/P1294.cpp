#include <stdio.h>
#include <stdlib.h>

#define MAX 21

int n, m;
int adj[MAX][MAX];
long long max_sum = 0;

void dfs(int u, int visited, long long current_sum) {
    if (current_sum > max_sum) {
        max_sum = current_sum;
    }
    for(int v = 1; v <= n; v++) {
        if(adj[u][v] != -1 && !(visited & (1 << (v -1)))) {
            dfs(v, visited | (1 << (v -1)), current_sum + adj[u][v]);
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            adj[i][j] = -1;
        }
    }
    int u, v, w;
    for(int i=0;i<m;i++) {
        scanf("%d %d %d", &u, &v, &w);
        adj[u][v] = w;
        adj[v][u] = w;
    }
    for(int i=1;i<=n;i++) {
        dfs(i, 1 << (i-1), 0);
    }
    printf("%lld\n", max_sum);
    return 0;
}