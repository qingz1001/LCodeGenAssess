#include <stdio.h>

int main() {
    int a, b, n;
    scanf("%d%d", &a, &b);

    // 初始化结果数组
    int result[1000];
    int count = 0;

    // 找到最小的分数
    for (n = 1; n < b; n++) {
        if (a * n % b == 0) {
            result[count++] = n;
            a *= n;
            b *= n;
            break;
        }
    }

    // 使用埃及分数表示法
    while (a > 0) {
        for (n = 2; n < b; n++) {
            if (a * n % b == 0) {
                result[count++] = n;
                a *= n;
                b *= n;
                break;
            }
        }
    }

    // 输出结果
    for (int i = 0; i < count; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}