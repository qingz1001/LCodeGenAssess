#include <stdio.h>
#include <string.h>

#define MAX_LEN 100001
#define MOD 10007

int main() {
    int L;
    scanf("%d", &L);
    char s[MAX_LEN];
    scanf("%s", s);

    // 动态规划数组，dp[i][j]表示第i个位置填j（0或1）时表达式的值为0的方案数
    int dp[MAX_LEN][2];
    int stack[MAX_LEN];
    int top = 0;

    // 初始化第一个位置
    dp[0][0] = 1;
    dp[0][1] = 1;

    for (int i = 0; i < L; i++) {
        if (s[i] == '(') {
            // 遇到左括号，压栈
            stack[top++] = i;
        } else if (s[i] == ')') {
            // 遇到右括号，弹栈并计算括号内的值
            int j = stack[--top];
            int temp0 = 0, temp1 = 0;
            for (int k = j + 1; k < i; k++) {
                if (s[k] == '0') {
                    temp0 = (temp0 + dp[k][0]) % MOD;
                    temp1 = (temp1 + dp[k][1]) % MOD;
                } else if (s[k] == '1') {
                    temp0 = (temp0 + dp[k][1]) % MOD;
                    temp1 = (temp1 + dp[k][0]) % MOD;
                } else if (s[k] == '+') {
                    temp0 = (temp0 * dp[k + 1][0] + temp1 * dp[k + 1][1]) % MOD;
                    temp1 = (temp0 * dp[k + 1][1] + temp1 * dp[k + 1][0]) % MOD;
                } else if (s[k] == '*') {
                    temp0 = (temp0 * dp[k + 1][0]) % MOD;
                    temp1 = (temp1 * dp[k + 1][1]) % MOD;
                }
            }
            dp[j][0] = temp0;
            dp[j][1] = temp1;
        } else if (s[i] == '0' || s[i] == '1') {
            // 遇到数字，直接更新dp数组
            dp[i + 1][0] = dp[i][0];
            dp[i + 1][1] = dp[i][1];
        } else if (s[i] == '+') {
            // 遇到加号，更新dp数组
            dp[i + 1][0] = (dp[i][0] * dp[i + 1][0] + dp[i][1] * dp[i + 1][1]) % MOD;
            dp[i + 1][1] = (dp[i][0] * dp[i + 1][1] + dp[i][1] * dp[i + 1][0]) % MOD;
        } else if (s[i] == '*') {
            // 遇到乘号，更新dp数组
            dp[i + 1][0] = (dp[i][0] * dp[i + 1][0]) % MOD;
            dp[i + 1][1] = (dp[i][1] * dp[i + 1][1]) % MOD;
        }
    }

    // 输出最终结果
    printf("%d\n", dp[L][0]);
    return 0;
}