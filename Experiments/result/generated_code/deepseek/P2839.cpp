#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20000
#define MAXQ 25000

int n, Q;
int a[MAXN];
int queries[MAXQ][4];
int answers[MAXQ];

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int find_median(int *arr, int len) {
    qsort(arr, len, sizeof(int), cmp);
    return arr[len / 2];
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

        int len = d - a + 1;
        int subarray[len];
        for (int j = 0; j < len; j++) {
            subarray[j] = a[a + j];
        }

        x = find_median(subarray, len);
        answers[i] = x;
    }

    for (int i = 0; i < Q; i++) {
        printf("%d\n", answers[i]);
    }

    return 0;
}