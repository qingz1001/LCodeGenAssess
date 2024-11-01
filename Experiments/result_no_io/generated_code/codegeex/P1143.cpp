#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    int n, m;
    char s[1000];
    scanf("%d %s %d", &n, s, &m);
    int len = strlen(s);
    long long decimal = 0;

    // 将n进制数转换为十进制数
    for (int i = 0; i < len; i++) {
        if (isdigit(s[i])) {
            decimal = decimal * n + (s[i] - '0');
        } else {
            decimal = decimal * n + (s[i] - 'A' + 10);
        }
    }

    // 将十进制数转换为m进制数
    char result[1000];
    int index = 0;
    while (decimal > 0) {
        int remainder = decimal % m;
        if (remainder < 10) {
            result[index++] = remainder + '0';
        } else {
            result[index++] = remainder - 10 + 'A';
        }
        decimal /= m;
    }
    result[index] = '\0';

    // 反转结果字符串
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - i - 1];
        result[index - i - 1] = temp;
    }

    // 输出结果
    printf("%s\n", result);

    return 0;
}