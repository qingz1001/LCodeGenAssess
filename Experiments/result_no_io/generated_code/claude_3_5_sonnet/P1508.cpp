#include <stdio.h>
#include <string.h>

#define MAX_N 200
#define MAX_M 200
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int m, n;
int food[MAX_M][MAX_N];
int dp[MAX_M][MAX_N];

int main() {
    scanf("%d %d", &m, &n);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &food[i][j]);
        }
    }
    
    memset(dp, 0x80, sizeof(dp)); // Initialize with very small values
    
    int start = n / 2;
    dp[m-1][start] = food[m-1][start];
    
    for (int i = m - 2; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            int left = (j > 0) ? dp[i+1][j-1] : 0x80000000;
            int mid = dp[i+1][j];
            int right = (j < n-1) ? dp[i+1][j+1] : 0x80000000;
            
            dp[i][j] = food[i][j] + MAX(MAX(left, mid), right);
        }
    }
    
    int maxEnergy = 0x80000000;
    for (int j = 0; j < n; j++) {
        maxEnergy = MAX(maxEnergy, dp[0][j]);
    }
    
    printf("%d\n", maxEnergy);
    
    return 0;
}