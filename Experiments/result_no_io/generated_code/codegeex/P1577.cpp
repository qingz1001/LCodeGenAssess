#include <stdio.h>

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    double min_len = 100000.00; // 初始化最小长度为100000.00
    double max_len = 0.00;      // 初始化最大长度为0.00

    for (int i = 0; i < N; i++) {
        double length;
        scanf("%lf", &length);

        if (length < min_len) {
            min_len = length; // 更新最小长度
        }

        if (length > max_len) {
            max_len = length; // 更新最大长度
        }
    }

    // 计算每条绳子的最大长度
    double max_cut_length = max_len / K;

    // 如果最大切割长度大于最小绳子长度，则输出最大切割长度
    if (max_cut_length > min_len) {
        printf("%.2f\n", max_cut_length);
    } else {
        printf("%.2f\n", min_len); // 否则输出最小绳子长度
    }

    return 0;
}