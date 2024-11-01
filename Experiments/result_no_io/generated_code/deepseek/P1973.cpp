#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200
#define INF 0x3f3f3f3f

typedef struct {
    int start, end;
} Event;

Event events[MAXN];
int dp[MAXN][MAXN];
int n;

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int cmp(const void *a, const void *b) {
    return ((Event *)a)->start - ((Event *)b)->start;
}

void solve() {
    qsort(events, n, sizeof(Event), cmp);

    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (dp[i][j] == -1) continue;
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j]);
            for (int k = i + 1; k < n; k++) {
                if (events[k].start >= events[i].end) {
                    dp[k + 1][j + 1] = max(dp[k + 1][j + 1], dp[i][j] + 1);
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, min(i, dp[n][i]));
    }
    printf("%d\n", ans);

    for (int i = 0; i < n; i++) {
        int ans_i = 0;
        for (int j = 0; j <= i; j++) {
            for (int k = i; k < n; k++) {
                if (dp[k][j] != -1) {
                    ans_i = max(ans_i, min(j + 1, dp[k][j]));
                }
            }
        }
        printf("%d\n", ans_i);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &events[i].start, &events[i].end);
        events[i].end += events[i].start;
    }
    solve();
    return 0;
}