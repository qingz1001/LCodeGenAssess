#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 501
#define MAXM 10001

int c, n;
int x[MAXN], y[MAXN];
int cnt[MAXM][MAXM];
bool vis[MAXM][MAXM];

bool check(int side) {
    memset(cnt, 0, sizeof(cnt));
    memset(vis, 0, sizeof(vis));

    for (int i = 0; i < n; i++) {
        for (int j = x[i]; j < x[i] + side; j++) {
            for (int k = y[i]; k < y[i] + side; k++) {
                cnt[j][k]++;
                if (cnt[j][k] == 1) vis[j][k] = true;
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < MAXM; i++) {
        for (int j = 0; j < MAXM; j++) {
            if (vis[i][j]) sum++;
        }
    }

    return sum >= c;
}

int main() {
    scanf("%d%d", &c, &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }

    int left = 1, right = 10000, ans = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}