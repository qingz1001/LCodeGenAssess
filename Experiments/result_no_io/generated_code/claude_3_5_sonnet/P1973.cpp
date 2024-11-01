#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200
#define MAX_M 400

typedef struct {
    int start;
    int end;
} Activity;

Activity activities[MAX_N];
int n;
int dp[MAX_M][MAX_M];
int prev[MAX_M];

int compare(const void* a, const void* b) {
    return ((Activity*)a)->end - ((Activity*)b)->end;
}

void solve() {
    int m = 0;
    for (int i = 0; i < n; i++) {
        prev[m] = activities[i].start;
        m++;
        prev[m] = activities[i].end;
        m++;
    }
    qsort(prev, m, sizeof(int), compare);
    m = unique(prev, prev + m) - prev;

    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++) {
        int s = lower_bound(prev, prev + m, activities[i].start) - prev;
        int e = lower_bound(prev, prev + m, activities[i].end) - prev;
        for (int j = 0; j < m; j++) {
            dp[e][j] = (dp[e][j] > dp[s][j] + 1) ? dp[e][j] : dp[s][j] + 1;
            dp[j][e] = (dp[j][e] > dp[j][s] + 1) ? dp[j][e] : dp[j][s] + 1;
        }
    }

    int ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int min = (dp[i][j] < dp[j][i]) ? dp[i][j] : dp[j][i];
            ans = (ans > min) ? ans : min;
        }
    }
    printf("%d\n", ans);

    for (int k = 0; k < n; k++) {
        int s = lower_bound(prev, prev + m, activities[k].start) - prev;
        int e = lower_bound(prev, prev + m, activities[k].end) - prev;
        int max_ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (i != e && j != e) {
                    int v1 = dp[i][j];
                    int v2 = (i < s) ? dp[i][s] + 1 : dp[i][e];
                    int v3 = (j < s) ? dp[s][j] + 1 : dp[e][j];
                    int min = (v2 < v3) ? v2 : v3;
                    max_ans = (max_ans > min) ? max_ans : min;
                }
            }
        }
        printf("%d\n", max_ans);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &activities[i].start, &activities[i].end);
        activities[i].end += activities[i].start;
    }
    solve();
    return 0;
}