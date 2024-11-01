#include <stdio.h>
#include <string.h>

// 定义一个数组来存储大数的每一位
char s[210];

int main() {
    int n;
    scanf("%d", &n);

    // 初始化s数组，s[0]为1表示大数的最低位为1
    s[0] = 1;
    int len = 1; // 大数的长度

    // 通过快速幂计算2^(2^n) - 1
    for (int i = 1; i <= n; i++) {
        // 对大数进行平方
        for (int j = 0; j < len; j++) {
            for (int k = 0; k < len; k++) {
                s[j + k] += s[j] * s[k];
            }
        }

        // 处理进位
        for (int j = 0; j < len; j++) {
            if (s[j] >= 10) {
                s[j + 1] += s[j] / 10;
                s[j] %= 10;
            }
        }

        // 如果最高位有进位，增加长度
        if (s[len] > 0) {
            len++;
        }
    }

    // 减去1
    for (int i = 0; i < len; i++) {
        s[i]--;
    }

    // 处理进位
    for (int i = 0; i < len; i++) {
        if (s[i] < 0) {
            s[i] += 10;
            s[i + 1]--;
        }
    }

    // 如果最高位为0，减小长度
    while (len > 1 && s[len - 1] == 0) {
        len--;
    }

    // 输出结果
    for (int i = len - 1; i >= 0; i--) {
        printf("%d", s[i]);
    }

    return 0;
}