#include <stdio.h>
#include <string.h>

#define MAX_LEN 501

int main() {
    char a[MAX_LEN], b[MAX_LEN];
    int result[MAX_LEN] = {0};
    int carry = 0;

    // 读取输入的两个大数
    scanf("%s", a);
    scanf("%s", b);

    // 从低位到高位逐位相加
    int len_a = strlen(a);
    int len_b = strlen(b);
    for (int i = 0; i < MAX_LEN; i++) {
        if (i < len_a) {
            result[i] += a[len_a - 1 - i] - '0';
        }
        if (i < len_b) {
            result[i] += b[len_b - 1 - i] - '0';
        }
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }

    // 找到结果中最高位的非零位
    int pos = MAX_LEN - 1;
    while (pos > 0 && result[pos] == 0) {
        pos--;
    }

    // 输出结果
    for (int i = pos; i >= 0; i--) {
        printf("%d", result[i]);
    }
    printf("\n");

    return 0;
}