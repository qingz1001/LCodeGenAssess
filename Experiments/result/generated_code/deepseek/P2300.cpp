#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    int *p = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    int count = 0;
    for (int i = 1; i < n; i++) {
        if (p[i] < p[i - 1]) {
            count += p[i - 1] - p[i];
            p[i] = p[i - 1];
        }
    }

    printf("%d\n", count);
    free(p);
    return 0;
}