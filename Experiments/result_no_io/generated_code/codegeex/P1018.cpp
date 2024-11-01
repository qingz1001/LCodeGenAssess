#include <stdio.h>
#include <string.h>

#define MAX_N 40
#define MAX_K 6

long long maxProduct[MAX_N][MAX_K + 1][MAX_N];
char digits[MAX_N + 1];

void calculateMaxProduct(int n, int k) {
    int i, j, l, m;
    long long product;

    // 初始化单个数字的最大乘积
    for (i = 0; i < n; i++) {
        maxProduct[i][0][i] = digits[i] - '0';
    }

    // 计算乘积
    for (j = 1; j <= k; j++) {
        for (i = 0; i < n - j; i++) {
            for (l = i; l < n - j; l++) {
                product = 1;
                for (m = i; m <= l; m++) {
                    product *= (digits[m] - '0');
                }
                maxProduct[i][j][l] = product;
                for (m = i; m < l; m++) {
                    maxProduct[i][j][l] = max(maxProduct[i][j][l], maxProduct[i][j - 1][m] * maxProduct[m + 1][1][l]);
                }
            }
        }
    }
}

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    scanf("%s", digits);

    calculateMaxProduct(n, k);

    printf("%lld\n", maxProduct[0][k][n - 1]);

    return 0;
}