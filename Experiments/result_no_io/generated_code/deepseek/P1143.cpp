#include <stdio.h>
#include <string.h>
#include <math.h>

// 将字符转换为对应的数值
int charToDigit(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1; // 非法字符
}

// 将数值转换为对应的字符
char digitToChar(int d) {
    if (d >= 0 && d <= 9) return d + '0';
    if (d >= 10 && d <= 15) return d - 10 + 'A';
    return '\0'; // 非法数值
}

// 将n进制字符串转换为十进制整数
long long nToDecimal(char *str, int n) {
    long long decimal = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        decimal = decimal * n + charToDigit(str[i]);
    }
    return decimal;
}

// 将十进制整数转换为m进制字符串
void decimalToM(long long decimal, int m, char *result) {
    int index = 0;
    while (decimal > 0) {
        result[index++] = digitToChar(decimal % m);
        decimal /= m;
    }
    result[index] = '\0';
    // 反转字符串
    int len = strlen(result);
    for (int i = 0; i < len / 2; i++) {
        char temp = result[i];
        result[i] = result[len - i - 1];
        result[len - i - 1] = temp;
    }
}

int main() {
    int n, m;
    char num[100];
    char result[100];

    scanf("%d", &n);
    scanf("%s", num);
    scanf("%d", &m);

    long long decimal = nToDecimal(num, n);
    decimalToM(decimal, m, result);

    printf("%s\n", result);

    return 0;
}