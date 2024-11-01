#include <stdio.h>
#include <stdlib.h>

#define MAXN 16005

int n;
int beauty[MAXN];
int graph[MAXN][MAXN];
int visited[MAXN];

void dfs(int node, int parent, long long *max_sum) {
    long long current_sum = beauty[node];
    for (int i = 1; i <= n; i++) {
        if (graph[node][i] && i != parent) {
            dfs(i, node, max_sum);
            current_sum += *(long long *)visited[i];
        }
    }
    *(long long *)visited[node] = current_sum;
    if (*max_sum < current_sum) {
        *max_sum = current_sum;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &beauty[i]);
    }
    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = 1;
        graph[b][a] = 1;
    }

    long long max_sum = 0;
    dfs(1, 0, &max_sum);

    printf("%lld\n", max_sum);

    return 0;
}