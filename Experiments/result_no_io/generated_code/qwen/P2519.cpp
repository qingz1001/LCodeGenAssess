#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &a[i], &b[i]);
    }

    int max_a = 0, max_b = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] > max_a) max_a = a[i];
        if (b[i] > max_b) max_b = b[i];
    }

    int result = n - (max_a + max_b + 1);

    printf("%d\n", result);

    free(a);
    free(b);

    return 0;
}