#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_LEN 1001

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void solve(char *num, int m, int *min_x, int *min_k, int *max_x, int *max_k) {
    int len = strlen(num);
    int dp[MAX_LEN][51] = {0};
    int k[MAX_LEN][51] = {0};
    
    for (int i = 0; i < len; i++) {
        int digit = num[i] - '0';
        for (int j = 0; j < m; j++) {
            if (i == 0) {
                dp[i][j] = digit % m;
                k[i][j] = 0;
            } else {
                int val1 = (dp[i-1][j] * 10 + digit) % m;
                int val2 = (j * digit) % m;
                if (dp[i-1][val2] + 1 < dp[i][val1] || (i == 1 && j == 0)) {
                    dp[i][val1] = dp[i-1][val2] + 1;
                    k[i][val1] = k[i-1][val2] + 1;
                } else {
                    dp[i][val1] = dp[i-1][val1];
                    k[i][val1] = k[i-1][val1];
                }
            }
        }
    }

    *min_x = m;
    *max_x = 0;
    for (int j = 0; j < m; j++) {
        if (dp[len-1][j] <= *min_x) {
            *min_x = j;
            *min_k = k[len-1][j];
        }
        if (dp[len-1][j] >= *max_x) {
            *max_x = j;
            *max_k = k[len-1][j];
        }
    }
}

int main() {
    char num[MAX_LEN];
    int m;
    scanf("%s", num);
    scanf("%d", &m);

    int min_x, min_k, max_x, max_k;
    solve(num, m, &min_x, &min_k, &max_x, &max_k);

    printf("%d %d %d %d\n", min_x, min_k, max_x, max_k);

    return 0;
}