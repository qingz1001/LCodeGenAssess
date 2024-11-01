#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int a[MAXN], u[MAXN], b[MAXN];
int m, n;

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &u[i]);
    }

    int j = 1, k = 1;
    for (int i = 1; i <= m; i++) {
        b[i] = a[i];
        qsort(b, i + 1, sizeof(int), cmp);
        while (j <= n && u[j] == i) {
            printf("%d\n", b[k]);
            k++;
            j++;
        }
    }

    return 0;
}