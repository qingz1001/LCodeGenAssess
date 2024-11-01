#include <stdio.h>
#include <stdlib.h>

#define MAXN 10
#define MAXVAL 100000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, i, j, k, l, count, *s, *x;
    int *sums;
    while (scanf("%d", &n) != EOF) {
        sums = (int*)malloc((n * (n - 1) / 2) * sizeof(int));
        for (i = 0; i < n * (n - 1) / 2; i++) {
            scanf("%d", &sums[i]);
        }
        qsort(sums, n * (n - 1) / 2, sizeof(int), compare);

        x = (int*)malloc(n * sizeof(int));
        s = (int*)malloc(n * sizeof(int));
        for (i = 0; i < n; i++) {
            x[i] = 0;
            s[i] = 0;
        }
        x[0] = sums[0] / 2;
        s[0] = sums[0] - x[0];
        count = 1;

        for (i = 1; i < n * (n - 1) / 2; i++) {
            for (j = 0; j < n; j++) {
                for (k = 0; k < n; k++) {
                    if (k != j) {
                        l = sums[i] - x[j] - x[k];
                        if (l >= 0 && l == x[j] + x[k]) {
                            x[k] = l;
                            s[k] = sums[i] - l;
                            count++;
                            break;
                        }
                    }
                }
                if (count == n) {
                    break;
                }
            }
            if (count != n) {
                break;
            }
        }

        if (count == n) {
            qsort(x, n, sizeof(int), compare);
            for (i = 0; i < n; i++) {
                printf("%d ", x[i]);
            }
            printf("\n");
        } else {
            printf("Impossible\n");
        }

        free(sums);
        free(x);
        free(s);
    }
    return 0;
}