#include <stdio.h>
#include <string.h>

int main() {
    int n, m;
    char s[100];
    int a[100];
    int i, j, len, num = 0;

    // 读取输入的进制n
    scanf("%d", &n);
    // 读取n进制数
    scanf("%s", s);
    // 读取转换后的进制m
    scanf("%d", &m);

    len = strlen(s);

    // 将n进制数转换为十进制数
    for (i = 0; i < len; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            a[i] = s[i] - '0';
        } else {
            a[i] = s[i] - 'A' + 10;
        }
        num = num * n + a[i];
    }

    // 将十进制数转换为m进制数
    char result[100];
    i = 0;
    while (num > 0) {
        int digit = num % m;
        if (digit < 10) {
            result[i++] = '0' + digit;
        } else {
            result[i++] = 'A' + digit - 10;
        }
        num /= m;
    }

    // 反转结果并输出
    for (j = i - 1; j >= 0; j--) {
        printf("%c", result[j]);
    }

    return 0;
}