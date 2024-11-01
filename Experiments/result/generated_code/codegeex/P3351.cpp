#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005
#define MAXM 200005

int n, m;
int u[MAXM], v[MAXM];
int *fa, *size;

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void union_sets(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        if (size[fx] < size[fy]) {
            fa[fx] = fy;
            size[fy] += size[fx];
        } else {
            fa[fy] = fx;
            size[fx] += size[fy];
        }
    }
}

bool is_connected() {
    for (int i = 1; i <= n; i++) {
        if (fa[i] != 1) return false;
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    fa = (int*)calloc(n + 1, sizeof(int));
    size = (int*)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        size[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d%d", u + i, v + i);
        union_sets(u[i], v[i]);
        if (is_connected()) {
            printf("%d\n", (n - 1) * n / 2);
            free(fa);
            free(size);
            return 0;
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        size[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        union_sets(u[i], v[i]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (find(i) == find(j)) {
                ans++;
            }
        }
    }

    printf("%d\n", ans);
    free(fa);
    free(size);
    return 0;
}