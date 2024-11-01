#include <stdio.h>

int a[10], n;
int ans = 0;

int check(int x) {
    int t = 1;
    for (int i = 1; i <= x; i++) t *= 10;
    return t;
}

void dfs(int k, int s, int t1, int t2, int t3, int t4) {
    if (k == n + 1) {
        if (t1 * 100 + t2 * 10 + t3 == t3 * 100 + t2 * 10 + t4 && t2 * t1 == t4 * 100 + t3 * 10 + s)
            ans++;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] == 0) continue;
        if (k == 1 && t1 != 0 && t1 * 10 + a[i] < t2 * 100 + t3 * 10 + t4) continue;
        if (k == 2 && t2 != 0 && t2 * 10 + a[i] < t3 * 100 + t4 * 10 + s) continue;
        if (k == 3 && t3 != 0 && t3 * 10 + a[i] < t4 * 10 + s) continue;
        if (k == 4 && t4 != 0 && t4 * 10 + a[i] < s) continue;
        a[i] = 0;
        if (k == 1) dfs(k + 1, s, t1 * 10 + a[i], t2, t3, t4);
        if (k == 2) dfs(k + 1, s, t1, t2 * 10 + a[i], t3, t4);
        if (k == 3) dfs(k + 1, s, t1, t2, t3 * 10 + a[i], t4);
        if (k == 4) dfs(k + 1, s, t1, t2, t3, t4 * 10 + a[i]);
        a[i] = 1;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i] = 1;
    }
    dfs(1, 0, 0, 0, 0, 0);
    printf("%d\n", ans);
    return 0;
}