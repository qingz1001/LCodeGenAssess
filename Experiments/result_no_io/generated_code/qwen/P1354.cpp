#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 1e9

int main() {
    int n;
    scanf("%d", &n);
    
    double walls[20][4];
    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf %lf %lf %lf", &walls[i][0], &walls[i][1], &walls[i][2], &walls[i][3]);
    }
    
    double dp[11] = {0};
    for (int i = 1; i <= 10; ++i) {
        dp[i] = INF;
    }
    dp[0] = 0;
    
    for (int i = 0; i < n; ++i) {
        double x = walls[i][0];
        double a1 = walls[i][1], b1 = walls[i][2], a2 = walls[i][3], b2 = walls[i][4];
        
        double new_dp[11];
        for (int j = 0; j <= 10; ++j) {
            new_dp[j] = INF;
        }
        
        for (int j = 0; j <= 10; ++j) {
            if (dp[j] == INF) continue;
            
            if (j >= a1 && j <= b1) {
                new_dp[j] = fmin(new_dp[j], dp[j] + abs(j - a2));
                new_dp[j] = fmin(new_dp[j], dp[j] + abs(j - b2));
            } else if (j >= a2 && j <= b2) {
                new_dp[j] = fmin(new_dp[j], dp[j] + abs(j - a1));
                new_dp[j] = fmin(new_dp[j], dp[j] + abs(j - b1));
            } else {
                new_dp[j] = fmin(new_dp[j], dp[j] + abs(j - x));
            }
        }
        
        for (int j = 0; j <= 10; ++j) {
            dp[j] = new_dp[j];
        }
    }
    
    printf("%.2f\n", dp[10]);
    
    return 0;
}