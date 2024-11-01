#include <stdio.h>
#include <stdlib.h>

#define MAXN 13
#define MAXA 500005
#define MOD 1000000007

int n, l, r;
int a[MAXN];

void dfs(int pos, int sum, int *cnt) {
    if (pos == n) {
        if (sum >= l && sum <= r) {
            (*cnt)++;
        }
        return;
    }
    for (int i = 0; i * a[pos] <= r - sum; i++) {
        dfs(pos + 1, sum + i * a[pos], cnt);
    }
}

int main() {
    scanf("%d %lld %lld", &n, &l, &r);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int ans = 0;
    dfs(0, 0, &ans);

    printf("%d\n", ans);
    return 0;
}