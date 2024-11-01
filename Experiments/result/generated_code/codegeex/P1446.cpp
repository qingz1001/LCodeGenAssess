#include <stdio.h>

int main() {
    int S_r, S_b, S_g, m, P;
    scanf("%d %d %d %d %d", &S_r, &S_b, &S_g, &m, &P);

    // 计算总的牌数 n
    int n = S_r + S_b + S_g;

    // 计算组合数 C(n, k) % P
    int factorial[n+1];
    factorial[0] = 1;
    for (int i = 1; i <= n; i++) {
        factorial[i] = factorial[i-1] * i % P;
    }

    int inverse_factorial[n+1];
    inverse_factorial[n] = 1;
    for (int i = n-1; i >= 0; i--) {
        inverse_factorial[i] = inverse_factorial[i+1] * (i+1) % P;
    }

    int C(int n, int k) {
        if (k > n || k < 0) return 0;
        return factorial[n] * inverse_factorial[k] % P * inverse_factorial[n-k] % P;
    }

    // 计算不同染色方案的数量
    int result = C(n, S_r) * C(n-S_r, S_b) % P * C(n-S_r-S_b, S_g) % P;

    // 计算不同洗牌方案下的染色方案数量
    for (int i = 0; i < m; i++) {
        int permutation[n];
        for (int j = 0; j < n; j++) {
            scanf("%d", &permutation[j]);
        }

        // 计算洗牌后的染色方案数量
        int permuted_result = C(n, S_r) * C(n-S_r, S_b) % P * C(n-S_r-S_b, S_g) % P;

        // 检查是否是新的方案
        int is_new = 1;
        for (int j = 0; j < i; j++) {
            int same = 1;
            for (int k = 0; k < n; k++) {
                if (permutation[k] != permutation[j]) {
                    same = 0;
                    break;
                }
            }
            if (same) {
                is_new = 0;
                break;
            }
        }

        if (is_new) {
            result = (result + permuted_result) % P;
        }
    }

    printf("%d\n", result);
    return 0;
}