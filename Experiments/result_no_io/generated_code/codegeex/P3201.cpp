#include <stdio.h>
#include <string.h>

int n, m, a[100005], fa[1000005], sum[1000005], cnt[1000005];

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void union_set(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        fa[fx] = fy;
        sum[fy] += sum[fx];
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= 1000000; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        int x = find(a[i]);
        cnt[x]++;
        sum[x]++;
    }
    for (int i = 1; i <= m; i++) {
        int op, x, y;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &x, &y);
            if (x == y) continue;
            int fx = find(x), fy = find(y);
            if (cnt[fx] < cnt[fy]) {
                union_set(fx, fy);
            } else {
                union_set(fy, fx);
            }
        } else if (op == 2) {
            int ans = 0;
            for (int i = 1; i <= 1000000; i++) {
                if (fa[i] == i && cnt[i] > 0) ans += sum[i];
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}