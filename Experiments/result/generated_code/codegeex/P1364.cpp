#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 101

int n;
int population[MAXN];
int left[MAXN], right[MAXN];
int minDistanceSum = INT_MAX;

void dfs(int node, int currentDistanceSum) {
    if (node == 0) {
        if (currentDistanceSum < minDistanceSum) {
            minDistanceSum = currentDistanceSum;
        }
        return;
    }

    if (left[node] != 0) {
        dfs(left[node], currentDistanceSum + population[node]);
    }
    if (right[node] != 0) {
        dfs(right[node], currentDistanceSum + population[node]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int w, u, v;
        scanf("%d %d %d", &w, &u, &v);
        population[i] = w;
        left[i] = u;
        right[i] = v;
    }

    for (int i = 1; i <= n; i++) {
        dfs(i, 0);
    }

    printf("%d\n", minDistanceSum);
    return 0;
}