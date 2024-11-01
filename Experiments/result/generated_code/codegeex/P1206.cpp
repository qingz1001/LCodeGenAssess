#include <stdio.h>
#include <string.h>

// 函数声明
void baseConversion(int num, int base, char *result);
int isPalindrome(char *str);

int main() {
    int B;
    scanf("%d", &B);

    for (int i = 1; i <= 300; i++) {
        int square = i * i;
        char numStr[20], squareStr[20];

        // 将i转换为B进制并存储在numStr中
        baseConversion(i, B, numStr);

        // 将square转换为B进制并存储在squareStr中
        baseConversion(square, B, squareStr);

        // 检查squareStr是否是回文数
        if (isPalindrome(squareStr)) {
            printf("%s %s\n", numStr, squareStr);
        }
    }

    return 0;
}

// 将一个十进制数转换为指定进制并存储在result字符串中
void baseConversion(int num, int base, char *result) {
    int index = 0;
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // 处理0的情况
    if (num == 0) {
        result[index++] = '0';
    }

    while (num > 0) {
        result[index++] = digits[num % base];
        num /= base;
    }

    // 翻转字符串
    result[index] = '\0';
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - i - 1];
        result[index - i - 1] = temp;
    }
}

// 检查一个字符串是否是回文数
int isPalindrome(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}