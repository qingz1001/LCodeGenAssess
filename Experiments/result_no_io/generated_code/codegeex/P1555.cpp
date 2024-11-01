#include <stdio.h>
#include <string.h>

int main() {
    char binary[32], ternary[32];
    int b[32], t[32], n, i, j, k, sum = 0;

    // 读取二进制和三进制表示
    scanf("%s", binary);
    scanf("%s", ternary);

    // 获取字符串长度
    n = strlen(binary);

    // 将二进制字符串转换为数组
    for (i = 0; i < n; i++) {
        b[i] = binary[n - i - 1] - '0';
    }

    // 将三进制字符串转换为数组
    for (i = 0; i < n; i++) {
        t[i] = ternary[n - i - 1] - '0';
    }

    // 找出错误位
    for (i = 0; i < n; i++) {
        // 将错误位设为1
        b[i] = 1 - b[i];
        int valid = 1;
        for (j = 0; j < n; j++) {
            int val = 0;
            for (k = 0; k < n; k++) {
                val = (val + b[k] * (int)pow(2, j - k)) % 3;
            }
            if (val != t[j]) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            break;
        }
        // 恢复错误位
        b[i] = 1 - b[i];
    }

    // 计算正确值
    for (i = 0; i < n; i++) {
        sum = (sum + b[i] * (int)pow(2, i)) % 3;
    }

    // 输出正确值
    printf("%d\n", sum);

    return 0;
}