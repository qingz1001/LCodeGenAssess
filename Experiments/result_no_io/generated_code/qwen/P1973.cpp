#include <stdio.h>
#include <stdlib.h>

#define MAXN 205

typedef struct {
    int start;
    int end;
} Activity;

int compare(const void *a, const void *b) {
    return ((Activity *)a)->start - ((Activity *)b)->start;
}

int main() {
    int n;
    scanf("%d", &n);
    Activity activities[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &activities[i].start, &activities[i].end);
        activities[i].end += activities[i].start;
    }

    qsort(activities, n, sizeof(Activity), compare);

    int dp[MAXN][2];
    dp[0][0] = 1;
    dp[0][1] = 0;

    for (int i = 1; i < n; i++) {
        if (activities[i].start >= activities[i-1].end) {
            dp[i][0] = dp[i-1][0] + 1;
            dp[i][1] = dp[i-1][1];
        } else {
            dp[i][0] = dp[i-1][0] + 1;
            dp[i][1] = dp[i-1][1] + 1;
        }
    }

    int maxActivities = dp[n-1][0] > dp[n-1][1] ? dp[n-1][0] : dp[n-1][1];

    printf("%d\n", maxActivities);

    for (int i = 0; i < n; i++) {
        int new_dp[MAXN][2];
        new_dp[0][0] = 1;
        new_dp[0][1] = 0;

        for (int j = 1; j < n; j++) {
            if (j == i) {
                new_dp[j][0] = dp[j-1][0];
                new_dp[j][1] = dp[j-1][1] + 1;
            } else if (activities[j].start >= activities[j-1].end) {
                new_dp[j][0] = dp[j-1][0] + 1;
                new_dp[j][1] = dp[j-1][1];
            } else {
                new_dp[j][0] = dp[j-1][0] + 1;
                new_dp[j][1] = dp[j-1][1] + 1;
            }
        }

        int new_maxActivities = new_dp[n-1][0] > new_dp[n-1][1] ? new_dp[n-1][0] : new_dp[n-1][1];
        printf("%d\n", new_maxActivities);
    }

    return 0;
}