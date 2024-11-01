#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int matrix[MAXN][MAXN];

int compare(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
        qsort(matrix[i], n, sizeof(int), compare);
    }

    for (int k = 0; k < q; k++) {
        int v;
        scanf("%d", &v);

        int count = 0;
        for (int j = 0; j < n; j++) {
            int valid = 0;
            for (int i = 0; i < n; i++) {
                if (matrix[i][j] >= v) {
                    valid = 1;
                    break;
                }
            }
            if (valid) {
                count++;
            }
        }

        printf("%d\n", count);
    }

    return 0;
}