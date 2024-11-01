#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 205
#define INF 0x3f3f3f3f

typedef struct {
    int start, end;
} Activity;

Activity activities[MAXN];
int n;
int dp[MAXN][MAXN];
int path[MAXN][MAXN];

int cmp(const void *a, const void *b) {
    return ((Activity*)a)->end - ((Activity*)b)->end;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void solve() {
    qsort(activities + 1, n, sizeof(Activity), cmp);
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -INF;
        }
    }
    dp[0][0] = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (activities[j].end <= activities[i].start) {
                for (int k = 0; k <= j; k++) {
                    if (dp[j][k] != -INF) {
                        if (dp[j][k] + 1 > dp[i][k + 1]) {
                            dp[i][k + 1] = dp[j][k] + 1;
                            path[i][k + 1] = j;
                        }
                        if (dp[j][k] > dp[i][k]) {
                            dp[i][k] = dp[j][k];
                            path[i][k] = j;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &activities[i].start, &activities[i].end);
        activities[i].end += activities[i].start;
    }
    
    solve();
    
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, i < n - i ? i : n - i);
    }
    printf("%d\n", ans);
    
    for (int i = 1; i <= n; i++) {
        Activity temp = activities[i];
        activities[i].start = -1;
        activities[i].end = INF;
        
        solve();
        
        int current_ans = 0;
        for (int j = 0; j <= n; j++) {
            current_ans = max(current_ans, j < n - j ? j : n - j);
        }
        printf("%d\n", current_ans);
        
        activities[i] = temp;
    }
    
    return 0;
}