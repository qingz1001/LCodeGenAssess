#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *p = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    int merges = 0;
    for (int i = 1; i < n; i++) {
        if (p[i] < p[i - 1]) {
            merges += (p[i - 1] - p[i]);
            p[i] = p[i - 1];
        }
    }

    printf("%d\n", merges);
    free(p);
    return 0;
}