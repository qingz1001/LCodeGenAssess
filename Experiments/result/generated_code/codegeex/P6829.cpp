#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200010

int n, k, q;
int r[MAXN];
int *g[MAXN];

void init(int kk, std::vector<int> rr) {
    k = kk;
    n = rr.size();
    for (int i = 0; i < n; i++) {
        r[i] = rr[i];
    }
    for (int i = 0; i < n; i++) {
        g[i] = (int *)malloc(sizeof(int) * (k + 1));
        memset(g[i], 0, sizeof(int) * (k + 1));
    }
    for (int i = 0; i < n; i++) {
        g[i][r[i]]++;
    }
    for (int i = 1; i < k; i++) {
        for (int j = 0; j < n; j++) {
            g[j][i] += g[j - 1][i - 1];
        }
    }
    for (int i = 0; i < n; i++) {
        g[i][k] += g[i - 1][k - 1];
    }
}

int compare_plants(int x, int y) {
    if (x == y) return 0;
    if (x == 0) {
        if (g[y][k - 1] == 0) return 1;
        else if (g[y][k - 1] == k - 1) return -1;
        else return 0;
    }
    if (y == 0) {
        if (g[x][k - 1] == 0) return -1;
        else if (g[x][k - 1] == k - 1) return 1;
        else return 0;
    }
    if (x < y) {
        if (g[y - 1][k - 1] == 0 && g[y - 1][k - 2] == 0) return 1;
        else if (g[y - 1][k - 1] == k - 1 && g[y - 1][k - 2] == k - 1) return -1;
        else return 0;
    } else {
        if (g[x - 1][k - 1] == 0 && g[x - 1][k - 2] == 0) return -1;
        else if (g[x - 1][k - 1] == k - 1 && g[x - 1][k - 2] == k - 1) return 1;
        else return 0;
    }
}

int main() {
    int n, k, q;
    scanf("%d %d %d", &n, &k, &q);
    std::vector<int> r(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &r[i]);
    }
    init(k, r);
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", compare_plants(x, y));
    }
    return 0;
}