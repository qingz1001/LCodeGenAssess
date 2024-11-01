#include <stdio.h>
#include <string.h>

// 函数声明
int isPalindrome(char str[]);
void decToBase(int num, int base, char result[]);

int main() {
    int B;
    scanf("%d", &B);

    for (int i = 1; i <= 300; i++) {
        char square[100];
        char baseI[100];
        decToBase(i * i, B, square);
        if (isPalindrome(square)) {
            decToBase(i, B, baseI);
            printf("%s %s\n", baseI, square);
        }
    }

    return 0;
}

// 判断字符串是否是回文
int isPalindrome(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

// 将十进制数转换为指定进制的字符串
void decToBase(int num, int base, char result[]) {
    char digits[] = "0123456789ABCDEFGHIJ";
    int index = 0;
    while (num > 0) {
        result[index++] = digits[num % base];
        num /= base;
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