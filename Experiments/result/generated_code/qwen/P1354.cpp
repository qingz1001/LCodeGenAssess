#include <stdio.h>
#include <math.h>

#define INF 1e9
#define EPS 1e-9

int main() {
    int n;
    scanf("%d", &n);
    
    double walls[20][5];
    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf %lf %lf %lf", &walls[i][0], &walls[i][1], &walls[i][2], &walls[i][3], &walls[i][4]);
    }
    
    double dp[11][11];
    for (int i = 0; i <= 10; ++i) {
        for (int j = 0; j <= 10; ++j) {
            dp[i][j] = INF;
        }
    }
    dp[0][5] = 0;
    
    for (int i = 0; i <= 10; ++i) {
        for (int j = 0; j <= 10; ++j) {
            if (dp[i][j] == INF) continue;
            
            for (int k = 0; k < n; ++k) {
                double x = walls[k][0];
                double a1 = walls[k][1], b1 = walls[k][2], a2 = walls[k][3], b2 = walls[k][4];
                
                if (i >= x - EPS && i <= x + EPS) {
                    if (j > a1 && j < b1) {
                        dp[x][b1] = fmin(dp[x][b1], dp[i][j] + abs(j - b1));
                    } else if (j > a2 && j < b2) {
                        dp[x][a2] = fmin(dp[x][a2], dp[i][j] + abs(j - a2));
                    }
                }
            }
            
            dp[i+1][j] = fmin(dp[i+1][j], dp[i][j] + 1);
            dp[i-1][j] = fmin(dp[i-1][j], dp[i][j] + 1);
            dp[i][j+1] = fmin(dp[i][j+1], dp[i][j] + 1);
            dp[i][j-1] = fmin(dp[i][j-1], dp[i][j] + 1);
        }
    }
    
    printf("%.2f\n", dp[10][5]);
    return 0;
}