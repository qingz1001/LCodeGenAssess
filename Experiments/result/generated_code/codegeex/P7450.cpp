#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 234
#define MAXM 100000

int T, n, m, k;
int c[MAXN][MAXN], a[MAXN][MAXN];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int vis[MAXN][MAXN], cnt;
int num[MAXM];
int ans = MAXM;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void dfs(int x, int y, int t) {
    if (cnt == t) return;
    vis[x][y] = 1;
    cnt++;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny] && c[nx][ny] != -1) {
            dfs(nx, ny, t);
        }
    }
}

int check(int mid) {
    int t = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] > mid) {
                num[++t] = a[i][j];
            }
        }
    }
    qsort(num + 1, t, sizeof(int), cmp);
    if (t < k) return 0;
    int l = 1, r = t, res = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int cnt = 0;
        for (int i = 1; i <= t; i++) {
            if (num[i] >= num[mid]) cnt++;
        }
        if (cnt >= k) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return num[res];
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &c[i][j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        int t = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (c[i][j] != -1) t++;
            }
        }
        if (t < k) {
            printf("-1 -1\n");
            continue;
        }
        int l = 0, r = MAXM;
        while (l <= r) {
            int mid = (l + r) >> 1;
            memset(vis, 0, sizeof(vis));
            cnt = 0;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    if (!vis[i][j] && c[i][j] != -1) {
                        dfs(i, j, mid);
                    }
                }
            }
            if (cnt >= k) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        int mid = (l + r) >> 1;
        int res = check(mid);
        if (res == 0) {
            printf("-1 -1\n");
        } else {
            printf("%d %d\n", mid, res);
        }
    }
    return 0;
}