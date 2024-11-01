#include <stdio.h>

int main() {
    int n, R;
    scanf("%d %d", &n, &R);

    // 处理负数情况
    int sign = 1;
    if (n < 0) {
        sign = -1;
        n = -n;
    }

    // 初始化结果字符串
    char result[40];
    int index = 0;

    // 负进制转换
    while (n != 0) {
        int remainder = n % R;
        n /= R;

        if (remainder < 0) {
            remainder += -R;
            n += 1;
        }

        if (remainder < 10) {
            result[index++] = '0' + remainder;
        } else {
            result[index++] = 'A' + remainder - 10;
        }
    }

    // 反转结果字符串
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - i - 1];
        result[index - i - 1] = temp;
    }

    // 输出结果
    printf("%d=", sign * n);
    for (int i = 0; i < index; i++) {
        printf("%c", result[i]);
    }
    printf("(base-%d)\n", -R);

    return 0;
}