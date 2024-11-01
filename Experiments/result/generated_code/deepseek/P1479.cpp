#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    // 计算所有可能的 k 值的和
    int sum_k = 0;

    // 计算 k 的可能值
    for (int k = 0; k <= 12; k++) {
        // 计算 n 颗棋子中选出 5 颗棋子的组合数
        int comb = 1;
        for (int i = 0; i < 5; i++) {
            comb *= (n - i);
            comb /= (i + 1);
        }

        // 计算 k 的值
        int k_value = comb * (k + 1);

        // 累加 k 的值
        sum_k += k_value;
    }

    // 输出结果
    printf("%d\n", sum_k);

    return 0;
}