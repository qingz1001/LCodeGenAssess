#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000

int main() {
    int n;
    scanf("%d", &n);

    int L[MAXN], R[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &L[i], &R[i]);
    }

    int minL = L[0], maxR = R[0];
    for (int i = 1; i < n; i++) {
        if (L[i] < minL) minL = L[i];
        if (R[i] > maxR) maxR = R[i];
    }

    int cost = 0;
    for (int i = 0; i < n; i++) {
        cost += (L[i] - minL) + (maxR - R[i]);
    }

    printf("%d\n", cost);
    return 0;
}