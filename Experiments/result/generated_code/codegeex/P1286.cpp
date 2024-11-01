#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int main() {
    int n, i, j, k, l;
    int *sum, *a, *b, *c, *d;
    int *used, *num;

    while (scanf("%d", &n) != EOF) {
        sum = (int *)malloc(sizeof(int) * (n * (n - 1) / 2));
        a = (int *)malloc(sizeof(int) * n);
        b = (int *)malloc(sizeof(int) * n);
        c = (int *)malloc(sizeof(int) * n);
        d = (int *)malloc(sizeof(int) * n);
        used = (int *)calloc(n, sizeof(int));
        num = (int *)malloc(sizeof(int) * n);

        for (i = 0; i < n * (n - 1) / 2; i++) {
            scanf("%d", &sum[i]);
        }

        a[0] = sum[0] / 2;
        a[1] = sum[0] - a[0];
        used[0] = 1;
        used[1] = 1;

        for (i = 1; i < n; i++) {
            num[i] = 0;
        }

        for (i = 1; i < n * (n - 1) / 2; i++) {
            for (j = 0; j < n; j++) {
                if (used[j] == 0) {
                    b[j] = sum[i] - a[j];
                    used[j] = 1;
                    break;
                }
            }

            for (j = 0; j < n; j++) {
                if (used[j] == 0) {
                    c[j] = b[j] - a[j];
                    d[j] = b[j] + a[j];
                    break;
                }
            }

            for (j = 0; j < n; j++) {
                if (used[j] == 0) {
                    if (c[j] < 0 || c[j] > MAX || d[j] < 0 || d[j] > MAX) {
                        printf("Impossible\n");
                        goto end;
                    }
                    num[j] = c[j];
                    a[j] = d[j];
                    used[j] = 1;
                    break;
                }
            }

            for (j = 0; j < n; j++) {
                if (used[j] == 0) {
                    num[j] = b[j];
                    used[j] = 1;
                    break;
                }
            }
        }

        for (i = 0; i < n; i++) {
            printf("%d ", num[i]);
        }
        printf("\n");

        end:
        free(sum);
        free(a);
        free(b);
        free(c);
        free(d);
        free(used);
        free(num);
    }

    return 0;
}