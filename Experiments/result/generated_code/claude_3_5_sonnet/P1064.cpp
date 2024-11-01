#include <stdio.h>
#include <string.h>

#define MAX_N 32001
#define MAX_M 61

int n, m;
int v[MAX_M], p[MAX_M], q[MAX_M];
int dp[MAX_N];

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &v[i], &p[i], &q[i]);
    }
    
    memset(dp, 0, sizeof(dp));
    
    for (int i = 1; i <= m; i++) {
        if (q[i] == 0) {  // 主件
            for (int j = n; j >= v[i]; j--) {
                // 不购买附件
                int case1 = dp[j - v[i]] + v[i] * p[i];
                
                // 购买一个附件
                int case2 = 0;
                for (int k = 1; k <= m; k++) {
                    if (q[k] == i && j >= v[i] + v[k]) {
                        int temp = dp[j - v[i] - v[k]] + v[i] * p[i] + v[k] * p[k];
                        if (temp > case2) case2 = temp;
                    }
                }
                
                // 购买两个附件
                int case3 = 0;
                for (int k1 = 1; k1 <= m; k1++) {
                    for (int k2 = k1 + 1; k2 <= m; k2++) {
                        if (q[k1] == i && q[k2] == i && j >= v[i] + v[k1] + v[k2]) {
                            int temp = dp[j - v[i] - v[k1] - v[k2]] + v[i] * p[i] + v[k1] * p[k1] + v[k2] * p[k2];
                            if (temp > case3) case3 = temp;
                        }
                    }
                }
                
                int max_value = case1 > case2 ? case1 : case2;
                max_value = max_value > case3 ? max_value : case3;
                
                if (max_value > dp[j]) dp[j] = max_value;
            }
        }
    }
    
    printf("%d\n", dp[n]);
    
    return 0;
}