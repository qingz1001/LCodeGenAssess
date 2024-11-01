#include <stdio.h>
#include <stdlib.h>

#define MAX_N 9
#define MAX_SUM 100000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, sums[MAX_N * (MAX_N - 1) / 2];
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n * (n - 1) / 2; ++i) {
            scanf("%d", &sums[i]);
        }
        qsort(sums, n * (n - 1) / 2, sizeof(int), compare);

        int found = 0;
        for (int a = 0; a <= MAX_SUM; ++a) {
            for (int b = a + 1; b <= MAX_SUM; ++b) {
                int count = 0;
                for (int i = 0; i < n * (n - 1) / 2; ++i) {
                    if (sums[i] == a + b) {
                        ++count;
                    }
                }
                if (count == n - 2) {
                    printf("%d %d ", a, b);
                    for (int c = b + 1; c <= MAX_SUM; ++c) {
                        if (sums[0] == a + c || sums[1] == a + c || sums[2] == a + c) {
                            printf("%d\n", c);
                            found = 1;
                            break;
                        }
                    }
                    break;
                }
            }
            if (found) break;
        }

        if (!found) {
            printf("Impossible\n");
        }
    }
    return 0;
}