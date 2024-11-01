#include <stdio.h>
#include <string.h>

// 判断一个字符串是否是回文数
int is_palindrome(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

// 将十进制数转换为指定进制的字符串
void to_base(int num, int base, char *result) {
    int index = 0;
    while (num > 0) {
        int remainder = num % base;
        result[index++] = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'A');
        num /= base;
    }
    result[index] = '\0';
    // 反转字符串
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - i - 1];
        result[index - i - 1] = temp;
    }
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);

    int count = 0;
    int current = s + 1;

    while (count < n) {
        int palindrome_count = 0;
        for (int base = 2; base <= 10; base++) {
            char result[33];
            to_base(current, base, result);
            if (is_palindrome(result)) {
                palindrome_count++;
            }
            if (palindrome_count >= 2) {
                break;
            }
        }
        if (palindrome_count >= 2) {
            printf("%d\n", current);
            count++;
        }
        current++;
    }

    return 0;
}