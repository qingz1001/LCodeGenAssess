#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30
#define MAX_VAL 1000000000

int n;
int score[MAX_N];
int dp[MAX_N][MAX_N];
int s[MAX_N][MAX_N];

void print_preorder(int l, int r) {
    if (l > r) return;
    printf("%d ", s[l][r]);
    print_preorder(l, s[l][r] - 1);
    print_preorder(s[l][r] + 1, r);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &score[i]);
    }

    // 初始化dp数组和s数组
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = 0;
            s[i][j] = 0;
        }
    }

    // 动态规划计算最大加分
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = MAX_VAL;
            for (int k = i; k <= j; k++) {
                int left = (i == k) ? 1 : dp[i][k - 1];
                int right = (j == k) ? 1 : dp[k + 1][j];
                if (dp[i][j] < left * right + score[k]) {
                    dp[i][j] = left * right + score[k];
                    s[i][j] = k;
                }
            }
        }
    }

    // 输出最高加分
    printf("%d\n", dp[1][n]);

    // 输出前序遍历
    print_preorder(1, n);
    printf("\n");

    return 0;
}