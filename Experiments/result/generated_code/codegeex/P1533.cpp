#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005
#define MAXM 50005

int a[MAXN];
int c[MAXN];
int n, m;

void init() {
    int i;
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        c[i] = a[i];
    }
    qsort(c + 1, n, sizeof(int), cmp);
}

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int find(int x) {
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (c[mid] < x) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

int main() {
    int i, j, k;
    scanf("%d%d", &n, &m);
    init();
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &j, &k, &i);
        printf("%d\n", c[find(n - j + k)]);
    }
    return 0;
}