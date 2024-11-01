#include <stdio.h>
#include <string.h>

#define MOD 19930726

int main() {
    int n, K;
    scanf("%d %d", &n, &K);
    char s[1000001];
    scanf("%s", s);

    int dp[1000001][27];
    int len[1000001];
    int count[1000001];
    int result = 1;

    // 初始化
    for (int i = 0; i < n; i++) {
        memset(dp[i], 0, sizeof(dp[i]));
        len[i] = 0;
        count[i] = 0;
    }

    // 预处理
    for (int i = 0; i < n; i++) {
        dp[i][s[i] - 'a'] = 1;
        for (int j = i - 1; j >= 0; j--) {
            if (dp[j][s[i] - 'a'] == 1) {
                if (s[j] == s[i]) {
                    len[i] = len[j] + 2;
                    break;
                }
            }
        }
        if (len[i] == 0) {
            len[i] = 1;
        }
        count[len[i]]++;
    }

    // 计算前K个和谐小群体的乘积
    for (int i = n; i >= 1; i--) {
        if (count[i] > 0) {
            K -= count[i];
            if (K < 0) {
                result = (long long)result * i % MOD;
                break;
            }
            result = (long long)result * i % MOD;
        }
    }

    if (K > 0) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}