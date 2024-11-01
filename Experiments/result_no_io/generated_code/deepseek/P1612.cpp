#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n;
int parent[MAXN];
long long weight[MAXN];
long long capacity[MAXN];
int result[MAXN];

void dfs(int u) {
    long long sum = 0;
    int length = 0;
    int v = u;
    while (v != 0 && sum + weight[v] <= capacity[u]) {
        sum += weight[v];
        length++;
        v = parent[v];
    }
    result[u] = length;
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &parent[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &weight[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &capacity[i]);
    }

    for (int i = 1; i <= n; i++) {
        dfs(i);
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}