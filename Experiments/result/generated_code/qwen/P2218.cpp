#include <stdio.h>
#include <stdlib.h>

#define MAXN 20005

int n;
int x[MAXN], y[MAXN];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    int minX = x[0], maxX = x[0];
    int minY = y[0], maxY = y[0];

    for (int i = 1; i < n; i++) {
        minX = min(minX, x[i]);
        maxX = max(maxX, x[i]);
        minY = min(minY, y[i]);
        maxY = max(maxY, y[i]);
    }

    int width = maxX - minX + 1;
    int height = maxY - minY + 1;

    int L = max(width, height);

    printf("%d\n", L);

    return 0;
}