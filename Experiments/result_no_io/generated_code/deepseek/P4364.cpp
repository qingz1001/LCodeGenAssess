#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005

int n;
double k;
int d[MAXN], result[MAXN];
int parent[MAXN];
int count[MAXN];

int compare(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

void solve() {
    qsort(d, n, sizeof(int), compare);

    for (int i = 1; i <= n; i++) {
        parent[i] = (int)(i / k);
        count[i] = 1;
    }

    for (int i = n; i >= 1; i--) {
        count[parent[i]] += count[i];
    }

    int idx = 0;
    for (int i = 1; i <= n; i++) {
        if (parent[i] == 0 || result[parent[i]] != 0) {
            result[i] = d[idx++];
        } else {
            result[i] = result[parent[i]];
        }
    }
}

int main() {
    scanf("%d %lf", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }

    solve();

    for (int i = 1; i <= n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}