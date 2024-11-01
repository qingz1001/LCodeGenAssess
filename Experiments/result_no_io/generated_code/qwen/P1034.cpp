#include <stdio.h>
#include <stdlib.h>

#define MAXN 55
#define MAXK 5

int points[MAXN][2];
int dp[MAXK][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i][0], &points[i][1]);
    }
    
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = (i == 0 && j == 0) ? 0 : INT_MAX / 2;
        }
    }
    
    for (int i = 1; i <= k; i++) {
        for (int j = i; j <= n; j++) {
            for (int l = 0; l < j; l++) {
                int maxX = -1, minX = 1001, maxY = -1, minY = 1001;
                for (int m = l; m < j; m++) {
                    if (points[m][0] > maxX) maxX = points[m][0];
                    if (points[m][0] < minX) minX = points[m][0];
                    if (points[m][1] > maxY) maxY = points[m][1];
                    if (points[m][1] < minY) minY = points[m][1];
                }
                dp[i][j] = min(dp[i][j], dp[i-1][l] + (maxX - minX) * (maxY - minY));
            }
        }
    }
    
    printf("%d\n", dp[k][n]);
    
    return 0;
}