#include <stdio.h>
#include <string.h>

#define MAXN 1000001
#define MAXM 1000001

int a[MAXN];
int cnt[MAXN];
int ans[MAXM];

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int l, r;
        scanf("%d %d", &l, &r);
        ans[i] = 0;
        memset(cnt, 0, sizeof(cnt));
        for (int j = l; j <= r; ++j) {
            if (!cnt[a[j]]) {
                ++ans[i];
            }
            ++cnt[a[j]];
        }
    }
    for (int i = 0; i < m; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}