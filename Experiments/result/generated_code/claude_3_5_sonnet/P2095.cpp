#include <stdio.h>
#include <string.h>

#define MAX_N 200
#define MAX_M 100
#define MAX_K 100

int n, m, k;
int max_per_category[MAX_K];
int fat[MAX_N];
int category[MAX_N];
int dp[MAX_M + 1][MAX_K + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    for (int i = 1; i <= k; i++) {
        scanf("%d", &max_per_category[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &fat[i], &category[i]);
    }
    
    memset(dp, 0, sizeof(dp));
    
    for (int i = 0; i < n; i++) {
        for (int j = m; j >= 1; j--) {
            for (int c = k; c >= 1; c--) {
                if (category[i] == c && max_per_category[c] > 0) {
                    dp[j][c] = max(dp[j][c], dp[j-1][c] + fat[i]);
                }
            }
        }
    }
    
    int result = 0;
    for (int j = 1; j <= m; j++) {
        for (int c = 1; c <= k; c++) {
            result = max(result, dp[j][c]);
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}