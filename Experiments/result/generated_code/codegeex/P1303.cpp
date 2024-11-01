#include <stdio.h>
#include <string.h>

#define MAXN 2005

int a[MAXN], b[MAXN], c[4000];

int main() {
    char str1[MAXN], str2[MAXN];
    int len1, len2, i, j;

    // 读取输入的两个非负整数
    scanf("%s%s", str1, str2);
    len1 = strlen(str1);
    len2 = strlen(str2);

    // 将字符串转换为数组并反转
    for (i = 0; i < len1; i++) {
        a[i] = str1[len1 - 1 - i] - '0';
    }
    for (i = 0; i < len2; i++) {
        b[i] = str2[len2 - 1 - i] - '0';
    }

    // 高精度乘法计算
    for (i = 0; i < len1; i++) {
        for (j = 0; j < len2; j++) {
            c[i + j] += a[i] * b[j];
            c[i + j + 1] += c[i + j] / 10;
            c[i + j] %= 10;
        }
    }

    // 找到结果的最高位
    int len3 = len1 + len2;
    while (len3 > 0 && c[len3 - 1] == 0) {
        len3--;
    }

    // 输出结果
    for (i = len3 - 1; i >= 0; i--) {
        printf("%d", c[i]);
    }

    return 0;
}