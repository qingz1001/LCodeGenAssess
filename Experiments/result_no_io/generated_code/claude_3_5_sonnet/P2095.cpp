#include <stdio.h>
#include <string.h>

#define MAX_N 201
#define MAX_M 101
#define MAX_K 101

int n, m, k;
int max_per_category[MAX_K];
int fat[MAX_N];
int category[MAX_N];
int dp[MAX_M][MAX_K];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    for (int i = 0; i < k; i++) {
        scanf("%d", &max_per_category[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &fat[i], &category[i]);
        category[i]--; // 将类别从1-based改为0-based
    }
    
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = m - 1; j >= 0; j--) {
            for (int c = 0; c < k; c++) {
                if (dp[j][c] != -1) {
                    int new_count = (c & (1 << category[i])) ? 
                        ((c >> category[i]) & 15) + 1 : 1;
                    if (new_count <= max_per_category[category[i]]) {
                        int new_category = (c & ~(15 << category[i])) | (new_count << category[i]);
                        dp[j+1][new_category] = max(dp[j+1][new_category], dp[j][c] + fat[i]);
                    }
                }
            }
        }
    }
    
    int result = 0;
    for (int j = 0; j <= m; j++) {
        for (int c = 0; c < (1 << (4 * k)); c++) {
            result = max(result, dp[j][c]);
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}