#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n;
int parent[MAXN];
long long weight[MAXN];
long long capacity[MAXN];
int result[MAXN];

void dfs(int u, long long current_weight, int current_length) {
    if (current_weight > capacity[u]) {
        return;
    }
    if (current_length > result[u]) {
        result[u] = current_length;
    }
    if (parent[u] != 0) {
        dfs(parent[u], current_weight + weight[parent[u]], current_length + 1);
    }
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
        dfs(i, weight[i], 1);
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}