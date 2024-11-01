#include <stdio.h>
#include <string.h>

#define MOD 50

int min_value, max_value;
int min_k_min, max_k_min;

void calculate(int num[], int len, int m) {
    if (len == 1) {
        min_value = max_value = num[0];
        min_k_min = max_k_min = 0;
        return;
    }

    int dp[len][len][MOD];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < len; i++) {
        dp[i][i][num[i] % m] = 1;
    }

    for (int l = 2; l <= len; l++) {
        for (int i = 0; i + l - 1 < len; i++) {
            int j = i + l - 1;
            for (int k = i; k < j; k++) {
                for (int x = 0; x < MOD; x++) {
                    for (int y = 0; y < MOD; y++) {
                        int product = ((long long)x * y) % m;
                        if (dp[i][k][x] && dp[k + 1][j][y]) {
                            dp[i][j][(product * num[j] % m)] += dp[i][k][x] * dp[k + 1][j][y];
                        }
                    }
                }
            }
        }
    }

    min_value = MOD;
    max_value = 0;
    min_k_min = max_k_min = 0;

    for (int x = 0; x < MOD; x++) {
        if (dp[0][len - 1][x] > 0) {
            if (x < min_value || (x == min_value && l < min_k_min)) {
                min_value = x;
                min_k_min = l;
            }
            if (x > max_value || (x == max_value && l < max_k_min)) {
                max_value = x;
                max_k_min = l;
            }
        }
    }
}

int main() {
    char str[1001];
    int m;
    scanf("%s %d", str, &m);

    int num[1000];
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        num[i] = str[i] - '0';
    }

    calculate(num, len, m);

    printf("%d %d %d %d\n", min_value, min_k_min, max_value, max_k_min);

    return 0;
}