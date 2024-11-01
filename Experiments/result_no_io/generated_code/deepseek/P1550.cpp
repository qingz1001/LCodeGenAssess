#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 300

int n;
int W[MAXN];
int P[MAXN][MAXN];
int minCost[MAXN];
int inSet[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int prim() {
    for (int i = 0; i < n; i++) {
        minCost[i] = W[i];
        inSet[i] = 0;
    }

    int totalCost = 0;
    minCost[n] = INT_MAX;

    for (int i = 0; i < n; i++) {
        int u = n;
        for (int j = 0; j < n; j++) {
            if (!inSet[j] && minCost[j] < minCost[u]) {
                u = j;
            }
        }

        inSet[u] = 1;
        totalCost += minCost[u];

        for (int v = 0; v < n; v++) {
            if (!inSet[v]) {
                minCost[v] = min(minCost[v], P[u][v]);
            }
        }
    }

    return totalCost;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &W[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &P[i][j]);
        }
    }

    int result = prim();
    printf("%d\n", result);

    return 0;
}