#include <stdio.h>

int main() {
    int n, s;
    scanf("%d %d", &n, &s);
    
    int a, b;
    scanf("%d %d", &a, &b);
    
    int x[5005], y[5005];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    
    int dp[1005] = {0}; // dp[i] 表示陶陶剩下 i 个力气时最多能摘到的苹果数
    
    for (int i = 0; i < n; i++) {
        for (int j = s; j >= y[i]; j--) {
            if (x[i] <= b || x[i] - a <= b) { // 如果陶陶能摘到这个苹果
                dp[j] = dp[j - y[i]] + 1;
            }
        }
    }
    
    int max_apples = 0;
    for (int i = 0; i <= s; i++) {
        if (dp[i] > max_apples) {
            max_apples = dp[i];
        }
    }
    
    printf("%d\n", max_apples);
    
    return 0;
}