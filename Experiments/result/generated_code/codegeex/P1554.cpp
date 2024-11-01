#include <stdio.h>

int main() {
    long long M, N;
    scanf("%lld %lld", &M, &N);

    int count[10] = {0};

    // 遍历从 M 到 N 的每一个数
    for (long long i = M; i <= N; ++i) {
        // 将当前数转换为字符串
        char str[20];
        sprintf(str, "%lld", i);

        // 统计每个数字出现的次数
        for (int j = 0; str[j] != '\0'; ++j) {
            count[str[j] - '0']++;
        }
    }

    // 输出结果
    for (int i = 0; i < 10; ++i) {
        printf("%d ", count[i]);
    }

    return 0;
}