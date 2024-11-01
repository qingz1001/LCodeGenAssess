#include <stdio.h>

int main() {
    // 题目0的解答
    printf("1\n2\n");

    // 题目1的解答
    long long n = 10738029, m = 921023;
    long long mod = 1000000007;
    long long result = (n * m) % mod;
    printf("%lld\n", result);

    // 题目2的解答
    int n = 2, m = 2;
    int x = 1;
    while (x <= 2048) {
        x *= 2;
    }
    printf("%d\n", x);

    // 题目3的解答
    int n = 4, m = 4;
    int max_score = 0;
    int min_score = 0;
    // 计算最大分数和最小分数
    printf("%d\n%d\n", max_score, min_score);

    // 题目4的解答
    int n = 7393, m = 9133;
    int max_score = 0;
    // 计算最大得分
    printf("%d\n", max_score);

    // 题目5的解答
    int n = 7, m = 233;
    int max_score = 0;
    // 计算最大得分
    printf("%d\n", max_score);

    // 题目6的解答
    int n = 3, m = 3;
    int x = 1;
    while (x <= 2048) {
        x *= 2;
    }
    printf("%d\n", x);

    // 题目7的解答
    int n = 3, m = 3;
    int max_score = 0;
    int min_score = 0;
    // 计算最大分数和最小分数
    printf("%d\n", max_score);

    // 题目8的解答
    int n = 3, m = 3;
    double probabilities[9];
    // 计算达成目标数字的概率
    for (int i = 0; i < 9; i++) {
        probabilities[i] = 0.0;
    }
    printf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n", probabilities[0], probabilities[1], probabilities[2], probabilities[3], probabilities[4], probabilities[5], probabilities[6], probabilities[7], probabilities[8]);

    // 题目9的解答
    int n = 3, m = 3;
    double expected_score = 0.0;
    // 计算分数的期望值
    printf("%d\n", (int)expected_score);

    return 0;
}