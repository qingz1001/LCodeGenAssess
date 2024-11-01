#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXD 50005

int main() {
    int N, D;
    scanf("%d %d", &N, &D);
    
    int H[MAXN];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &H[i]);
    }
    
    int dp[MAXD][MAXN];
    int prev[MAXD][MAXN];
    
    for (int d = 0; d < D; ++d) {
        for (int n = 0; n < N; ++n) {
            dp[d][n] = -1;
            prev[d][n] = -1;
        }
    }
    
    dp[0][0] = 0;
    prev[0][0] = 0;
    
    for (int d = 0; d < D; ++d) {
        for (int n = 0; n < N; ++n) {
            if (dp[d][n] == -1) continue;
            
            int happiness = dp[d][n] / 2;
            if (happiness >= H[n]) {
                if (d + 1 < D && dp[d + 1][n + 1] == -1 || dp[d + 1][n + 1] > happiness + H[n]) {
                    dp[d + 1][n + 1] = happiness + H[n];
                    prev[d + 1][n + 1] = n + 1;
                }
            }
        }
    }
    
    int max_happiness = -1;
    int end_day = -1;
    for (int d = 0; d < D; ++d) {
        for (int n = 0; n < N; ++n) {
            if (dp[d][n] != -1 && dp[d][n] > max_happiness) {
                max_happiness = dp[d][n];
                end_day = d;
            }
        }
    }
    
    printf("%d\n", max_happiness);
    
    int current_day = end_day;
    while (current_day >= 0) {
        int current_chocolate = prev[current_day][current_day];
        printf("%d\n", current_chocolate);
        current_day--;
    }
    
    return 0;
}