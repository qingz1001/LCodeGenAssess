#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 2001

int min(int a, int b, int c) {
    int m = a < b ? a : b;
    return m < c ? m : c;
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int main() {
    char A[MAX_LEN], B[MAX_LEN];
    int K;
    int dp[MAX_LEN][MAX_LEN];
    
    scanf("%s", A);
    scanf("%s", B);
    scanf("%d", &K);
    
    int lenA = strlen(A);
    int lenB = strlen(B);
    
    // 初始化dp数组
    for (int i = 0; i <= lenA; i++) {
        dp[i][0] = i * K;
    }
    for (int j = 0; j <= lenB; j++) {
        dp[0][j] = j * K;
    }
    
    // 填充dp数组
    for (int i = 1; i <= lenA; i++) {
        for (int j = 1; j <= lenB; j++) {
            int cost = abs(A[i-1] - B[j-1]);
            dp[i][j] = min(dp[i-1][j] + K, 
                           dp[i][j-1] + K, 
                           dp[i-1][j-1] + cost);
        }
    }
    
    // 输出结果
    printf("%d\n", dp[lenA][lenB]);
    
    return 0;
}