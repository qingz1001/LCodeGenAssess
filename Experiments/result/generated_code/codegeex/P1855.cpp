#include <stdio.h>

int main() {
    int n, M, T;
    scanf("%d %d %d", &n, &M, &T);
    
    int m[101], t[101];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &m[i], &t[i]);
    }
    
    int dp[201][201] = {0};
    
    for (int i = 0; i < n; i++) {
        for (int j = M; j >= m[i]; j--) {
            for (int k = T; k >= t[i]; k--) {
                dp[j][k] = (dp[j][k] > dp[j - m[i]][k - t[i]] + 1) ? dp[j][k] : dp[j - m[i]][k - t[i]] + 1;
            }
        }
    }
    
    int max_wishes = 0;
    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= T; j++) {
            max_wishes = (max_wishes > dp[i][j]) ? max_wishes : dp[i][j];
        }
    }
    
    printf("%d\n", max_wishes);
    return 0;
}