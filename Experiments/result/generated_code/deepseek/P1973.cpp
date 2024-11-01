#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200
#define INF 1000000000

typedef struct {
    int start, end;
} Event;

Event events[MAXN];
int dp[MAXN][MAXN];
int must_include[MAXN][MAXN];
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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -INF;
        }
    }

    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
        for (int j = i + 1; j < n; j++) {
            if (events[j].start >= events[i].end) {
                dp[i][j] = max(dp[i][j], dp[i][j - 1] + 1);
            } else {
                dp[i][j] = dp[i][j - 1];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        must_include[i][i] = 1;
        for (int j = i + 1; j < n; j++) {
            must_include[i][j] = must_include[i][j - 1];
            if (events[j].start >= events[i].end) {
                must_include[i][j] = max(must_include[i][j], must_include[i][j - 1] + 1);
            }
        }
    }

    int max_val = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            max_val = max(max_val, min(dp[0][i] + dp[j][n - 1], must_include[i][j]));
        }
    }

    printf("%d\n", max_val);

    for (int k = 0; k < n; k++) {
        int result = 0;
        for (int i = 0; i <= k; i++) {
            for (int j = k; j < n; j++) {
                result = max(result, min(dp[0][i] + dp[j][n - 1], must_include[i][j] + (i <= k && k <= j ? 1 : 0)));
            }
        }
        printf("%d\n", result);
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