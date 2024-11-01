#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005
#define MAXM 1000005

int a[MAXN];
int cnt[MAXN];
int ans[MAXM];

void add(int x) {
    if (cnt[x] == 0) {
        ans[ans[0]]++;
    }
    cnt[x]++;
}

void del(int x) {
    cnt[x]--;
    if (cnt[x] == 0) {
        ans[ans[0]]--;
    }
}

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        ans[i + 1] = ans[i];
    }
    for (int i = 1; i <= n; i++) {
        add(a[i]);
    }
    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        del(a[l - 1]);
        add(a[r]);
        printf("%d\n", ans[i]);
    }
    return 0;
}