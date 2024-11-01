#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200005
#define INF 1000000001

typedef long long ll;

int n;
int a[MAX_N], h[MAX_N], c[MAX_N];
int p[MAX_N], sz[MAX_N];

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (sz[x] < sz[y]) {
        p[x] = y;
        sz[y] += sz[x];
    } else {
        p[y] = x;
        sz[x] += sz[y];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i], &h[i], &c[i]);
        p[i] = i;
        sz[i] = 1;
    }

    for (int i = n; i >= 1; i--) {
        unite(i, a[i]);
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (find(i) != i) continue;
        int min_h = INF, min_c = INF;
        for (int j = 1; j <= n; j++) {
            if (find(j) != i) continue;
            if (h[j] < min_h) {
                min_h = h[j];
                min_c = c[j];
            } else if (h[j] == min_h && c[j] < min_c) {
                min_c = c[j];
            }
        }
        ans += min_c;
    }

    printf("%lld\n", ans);
    return 0;
}