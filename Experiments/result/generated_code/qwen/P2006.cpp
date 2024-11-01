#include <stdio.h>
#include <stdlib.h>

int main() {
    int k, m, n;
    scanf("%d %d %d", &k, &m, &n);

    int* a = (int*)malloc(m * sizeof(int));
    int* b = (int*)malloc(m * sizeof(int));

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }

    int result[m];
    int count = 0;

    for (int i = 0; i < m; i++) {
        if (a[i] <= k && b[i] > 0) {
            result[count++] = i + 1;
        }
    }

    if (count == 0) {
        printf("-1\n");
    } else {
        for (int i = 0; i < count - 1; i++) {
            printf("%d ", result[i]);
        }
        printf("%d\n", result[count - 1]);
    }

    free(a);
    free(b);

    return 0;
}