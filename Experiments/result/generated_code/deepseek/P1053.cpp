#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50000

int n;
int wishes[MAXN][2];
int positions[MAXN];
int temp[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int calculateCost(int start) {
    int cost = 0;
    for (int i = 0; i < n; i++) {
        temp[i] = positions[(start + i) % n];
    }
    for (int i = 0; i < n; i++) {
        int left = (i - 1 + n) % n;
        int right = (i + 1) % n;
        if (temp[left] != wishes[temp[i]][0] && temp[left] != wishes[temp[i]][1] &&
            temp[right] != wishes[temp[i]][0] && temp[right] != wishes[temp[i]][1]) {
            return INT_MAX;
        }
    }
    for (int i = 0; i < n; i++) {
        if (temp[i] != positions[i]) {
            cost++;
        }
    }
    return cost;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &wishes[i][0], &wishes[i][1]);
        wishes[i][0]--;
        wishes[i][1]--;
    }
    for (int i = 0; i < n; i++) {
        positions[i] = i;
    }

    int minCost = INT_MAX;
    for (int start = 0; start < n; start++) {
        minCost = min(minCost, calculateCost(start));
    }

    if (minCost == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", minCost);
    }

    return 0;
}