#include <stdio.h>
#include <stdlib.h>

#define MAXN 10010
#define MAXM 20010

int n, k, m;
int a[MAXM], b[MAXM], Ti[MAXM], ti[MAXM];
int fa[MAXN], rank[MAXN];

int find(int x) {
    if (fa[x] != x) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            fa[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            fa[rootX] = rootY;
        } else {
            fa[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int cmp(const void *a, const void *b) {
    int *x = (int *)a, *y = (int *)b;
    return *x - *y;
}

int main() {
    scanf("%d %d %d", &n, &k, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &a[i], &b[i], &Ti[i], &ti[i]);
        a[i]--;
        b[i]--;
    }

    for (int i = 0; i < n; i++) {
        fa[i] = i;
        rank[i] = 0;
    }

    int maxTime = 0;
    int cnt = 0;

    for (int i = 0; i < m; i++) {
        if (Ti[i] > ti[i]) {
            unionSets(a[i], b[i]);
        } else {
            cnt++;
            unionSets(a[i], b[i]);
            maxTime = ti[i];
        }
    }

    if (cnt < k) {
        qsort(ti, m, sizeof(int), cmp);
        for (int i = 0; i < m; i++) {
            if (cnt == k) {
                break;
            }
            cnt++;
            unionSets(a[i], b[i]);
            maxTime = ti[i];
        }
    }

    printf("%d\n", maxTime);

    return 0;
}