#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000000

int n;
int L[MAXN], R[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &L[i], &R[i]);
    }

    int minL = INT_MAX, maxR = INT_MIN;
    for (int i = 0; i < n; i++) {
        minL = min(minL, L[i]);
        maxR = max(maxR, R[i]);
    }

    int cost = 0;
    for (int i = 0; i < n; i++) {
        cost += (R[i] - L[i]) - (maxR - minL);
    }

    printf("%d\n", cost);
    return 0;
}