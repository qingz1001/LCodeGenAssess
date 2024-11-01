#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, M, T;
    int m[MAX_N], t[MAX_N];
    int dp[201][201] = {0};
    
    scanf("%d %d %d", &n, &M, &T);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &m[i], &t[i]);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = M; j >= m[i]; j--) {
            for (int k = T; k >= t[i]; k--) {
                dp[j][k] = max(dp[j][k], dp[j-m[i]][k-t[i]] + 1);
            }
        }
    }
    
    printf("%d\n", dp[M][T]);
    
    return 0;
}