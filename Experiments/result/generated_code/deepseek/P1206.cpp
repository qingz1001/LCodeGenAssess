#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 将十进制数转换为B进制字符串
void decimalToBaseB(int num, int base, char *result) {
    int index = 0;
    while (num > 0) {
        int remainder = num % base;
        if (remainder < 10) {
            result[index++] = remainder + '0';
        } else {
            result[index++] = remainder - 10 + 'A';
        }
        num /= base;
    }
    result[index] = '\0';
    // 反转字符串
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - 1 - i];
        result[index - 1 - i] = temp;
    }
}

// 检查字符串是否是回文
bool isPalindrome(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int B;
    scanf("%d", &B);

    for (int i = 1; i <= 300; i++) {
        int square = i * i;
        char baseB[100];
        char baseBSquare[100];

        decimalToBaseB(i, B, baseB);
        decimalToBaseB(square, B, baseBSquare);

        if (isPalindrome(baseBSquare)) {
            printf("%s %s\n", baseB, baseBSquare);
        }
    }

    return 0;
}