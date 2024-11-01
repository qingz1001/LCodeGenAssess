#include <stdio.h>

int main() {
    int N, X, i, j, count = 0;
    int perm[10];
    int fact[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880}; // 阶乘数组

    // 读取输入
    scanf("%d %d", &N, &X);

    // 初始化排列数组
    for (i = 1; i <= N; i++) {
        perm[i] = i;
    }

    // 计算字典序的排名
    for (i = 1; i <= N; i++) {
        for (j = i + 1; j <= N; j++) {
            if (perm[i] > perm[j]) {
                count++;
            }
        }
        // 将当前数字放到合适的位置
        for (j = i + 1; j <= N; j++) {
            if (perm[j] < perm[i]) {
                perm[j]++;
            }
        }
        perm[i] = 0;
    }

    // 输出结果
    printf("%d\n", count + 1);

    return 0;
}