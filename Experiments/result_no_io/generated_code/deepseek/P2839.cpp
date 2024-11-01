#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 20000
#define MAXQ 25000

int n, Q;
int a[MAXN];
int queries[MAXQ][4];
int results[MAXQ];

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int find_median(int l, int r) {
    int len = r - l + 1;
    int *subarray = malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) {
        subarray[i] = a[l + i];
    }
    qsort(subarray, len, sizeof(int), cmp);
    int median = subarray[len / 2];
    free(subarray);
    return median;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d", &queries[i][j]);
        }
    }

    int x = 0;
    for (int i = 0; i < Q; i++) {
        int q[4];
        for (int j = 0; j < 4; j++) {
            q[j] = (queries[i][j] + x) % n;
        }
        qsort(q, 4, sizeof(int), cmp);
        int a = q[0], b = q[1], c = q[2], d = q[3];
        int max_median = INT_MIN;
        for (int l = a; l <= b; l++) {
            for (int r = c; r <= d; r++) {
                if (l <= r) {
                    int median = find_median(l, r);
                    if (median > max_median) {
                        max_median = median;
                    }
                }
            }
        }
        results[i] = max_median;
        x = max_median;
    }

    for (int i = 0; i < Q; i++) {
        printf("%d\n", results[i]);
    }

    return 0;
}