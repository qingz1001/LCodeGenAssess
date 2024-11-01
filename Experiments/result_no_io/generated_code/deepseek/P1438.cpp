#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int a[MAXN];
int diff[MAXN];
int n, m;

void update(int l, int r, int K, int D) {
    diff[l] += K;
    if (r + 1 <= n) diff[r + 1] -= K + (r - l + 1) * D;
    if (l + 1 <= n) diff[l + 1] += D;
    if (r + 2 <= n) diff[r + 2] -= D;
}

void apply_diff() {
    for (int i = 1; i <= n; i++) {
        diff[i] += diff[i - 1];
        a[i] += diff[i];
    }
    for (int i = 0; i <= n; i++) diff[i] = 0;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    for (int i = 0; i < m; i++) {
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            int l, r, K, D;
            scanf("%d %d %d %d", &l, &r, &K, &D);
            update(l, r, K, D);
        } else if (opt == 2) {
            int p;
            scanf("%d", &p);
            apply_diff();
            printf("%d\n", a[p]);
        }
    }

    return 0;
}