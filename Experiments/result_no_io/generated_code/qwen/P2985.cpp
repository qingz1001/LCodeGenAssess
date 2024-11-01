#include <stdio.h>
#include <stdlib.h>

#define MAXN 50001
#define MAXD 50001
#define MAXH 1000000

int main() {
    int N, D;
    scanf("%d %d", &N, &D);

    int H[MAXN];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &H[i]);
    }

    long long dp[MAXD][MAXN];
    int path[MAXD][MAXN];

    for (int i = 0; i < D; ++i) {
        for (int j = 0; j < N; ++j) {
            dp[i][j] = -1;
        }
    }

    for (int i = 0; i < D; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == 0 && j == 0) {
                dp[0][0] = H[0];
                continue;
            }
            if (dp[i][j] != -1) {
                int prev_happiness = dp[i][j];
                if (j > 0) {
                    int new_happiness = prev_happiness / 2 + H[j];
                    if (dp[i][j-1] == -1 || dp[i][j-1] < new_happiness) {
                        dp[i][j-1] = new_happiness;
                        path[i][j-1] = j;
                    }
                }
                if (i > 0) {
                    int new_happiness = prev_happiness / 2 + H[j];
                    if (dp[i-1][j] == -1 || dp[i-1][j] < new_happiness) {
                        dp[i-1][j] = new_happiness;
                        path[i-1][j] = j;
                    }
                }
            }
        }
    }

    long long max_min_happiness = -1;
    int end_day = -1, end_chocolate = -1;

    for (int j = 0; j < N; ++j) {
        if (dp[D-1][j] != -1 && dp[D-1][j] > max_min_happiness) {
            max_min_happiness = dp[D-1][j];
            end_day = D-1;
            end_chocolate = j;
        }
    }

    printf("%lld\n", max_min_happiness);

    while (end_chocolate != -1) {
        printf("%d\n", end_chocolate + 1);
        int temp = end_chocolate;
        end_chocolate = path[end_day][temp];
        end_day--;
    }

    return 0;
}