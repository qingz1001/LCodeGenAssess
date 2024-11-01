#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define MAXM 500005
#define INF 0x3f3f3f3f

int n, m;
int a[MAXN];
int f[MAXN][MAXM];
int s[MAXN];
int q[MAXN], head, tail;

int cost(int i, int j) {
    return (s[j] - s[i]) - (j - i) * a[i];
}

void solve(int l, int r, int pl, int pr, int k) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    int best = pl;
    f[mid][k] = INF;
    for (int i = pl; i <= pr && i < mid; i++) {
        int val = f[i][k-1] + cost(i, mid);
        if (val < f[mid][k]) {
            f[mid][k] = val;
            best = i;
        }
    }
    solve(l, mid-1, pl, best, k);
    solve(mid+1, r, best, pr, k);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    // 预处理前缀和
    for (int i = 1; i <= n; i++) {
        s[i] = s[i-1] + a[i];
    }
    
    // 初始化
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    
    // DP
    for (int k = 1; k <= m; k++) {
        solve(1, n, 0, n-1, k);
    }
    
    printf("%d\n", f[n][m]);
    return 0;
}