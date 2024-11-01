#include <stdio.h>
#include <string.h>

int n, m;
int adj[20][20];
long long max_total = 0;

void dfs(int current, int visited, long long total) {
    if (total > max_total) {
        max_total = total;
    }
    for(int next = 0; next < n; next++) {
        if(adj[current][next] > 0 && !(visited & (1 << next))){
            dfs(next, visited | (1 << next), total + adj[current][next]);
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    memset(adj, 0, sizeof(adj));
    int a, b, w;
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &a, &b, &w);
        adj[a-1][b-1] = w;
        adj[b-1][a-1] = w;
    }
    for(int i = 0; i < n; i++){
        dfs(i, 1 << i, 0);
    }
    printf("%lld", max_total);
    return 0;
}