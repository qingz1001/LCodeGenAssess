#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DIGITS 10

bool isRunaround(unsigned int num) {
    char digits[MAX_DIGITS];
    int len = 0, visited = 0;
    bool used[10] = {false};

    // 将数字转换为字符数组并检查是否有重复数字
    while (num > 0) {
        int digit = num % 10;
        if (digit == 0 || used[digit]) return false;
        digits[len++] = digit + '0';
        used[digit] = true;
        num /= 10;
    }

    // 反转数字
    for (int i = 0; i < len / 2; i++) {
        char temp = digits[i];
        digits[i] = digits[len - 1 - i];
        digits[len - 1 - i] = temp;
    }

    int pos = 0;
    for (int i = 0; i < len; i++) {
        int step = digits[pos] - '0';
        visited |= (1 << pos);
        for (int j = 0; j < step; j++) {
            pos = (pos + 1) % len;
        }
        if (visited & (1 << pos)) {
            return (pos == 0 && visited == (1 << len) - 1);
        }
    }
    return false;
}

unsigned int findNextRunaround(unsigned int m) {
    m++;
    while (!isRunaround(m)) {
        m++;
    }
    return m;
}

int main() {
    unsigned int m;
    scanf("%u", &m);
    printf("%u\n", findNextRunaround(m));
    return 0;
}