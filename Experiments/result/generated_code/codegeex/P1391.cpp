#include <stdio.h>

int n, a[20][20], cnt[20], ans = 0x3f3f3f3f;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

void dfs(int x, int y, int step) {
    if (x == n) {
        ans = ans < step ? ans : step;
        return;
    }
    if (y == n) {
        dfs(x + 1, 1, step);
        return;
    }
    dfs(x, y + 1, step);
    if (a[x][y] == 0) {
        int tmp = cnt[x] + cnt[y] + cnt[n];
        if (tmp % 2 == 0) {
            a[x][y] = 1;
            dfs(x, y + 1, step + 1);
            a[x][y] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
            if (a[i][j] == 1) {
                for (int k = 0; k < 4; k++) {
                    cnt[i + dx[k]]++;
                    cnt[j + dy[k]]++;
                }
            }
        }
    }
    dfs(1, 1, 0);
    if (ans == 0x3f3f3f3f) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }
    return 0;
}