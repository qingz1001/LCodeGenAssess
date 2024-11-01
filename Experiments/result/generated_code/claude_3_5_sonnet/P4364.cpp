#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 500005

int n;
double k;
int d[MAX_N], result[MAX_N];

int cmp(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int main() {
    scanf("%d %lf", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }

    qsort(d, n, sizeof(int), cmp);

    int idx = 0;
    for (int i = 0; i < n; i++) {
        int parent = (int)floor(i / k);
        while (idx < n && (idx <= parent || result[parent] == 0)) {
            result[idx++] = d[i];
        }
        if (idx == n) break;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}