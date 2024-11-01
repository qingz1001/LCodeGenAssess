#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 300

int n;
int W[MAXN];
int P[MAXN][MAXN];
int minCost[MAXN];
int inMST[MAXN];

int prim() {
    for (int i = 0; i < n; i++) {
        minCost[i] = INT_MAX;
        inMST[i] = 0;
    }

    minCost[0] = 0;
    int totalCost = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (!inMST[i] && (u == -1 || minCost[i] < minCost[u])) {
                u = i;
            }
        }

        inMST[u] = 1;
        totalCost += minCost[u];

        for (int v = 0; v < n; v++) {
            if (!inMST[v] && (P[u][v] < minCost[v] || (u == v && W[u] < minCost[v]))) {
                minCost[v] = (u == v) ? W[u] : P[u][v];
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