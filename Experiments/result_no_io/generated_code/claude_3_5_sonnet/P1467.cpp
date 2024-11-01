#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DIGITS 10

bool isRunaround(int num) {
    char digits[MAX_DIGITS];
    int len = 0;
    bool visited[MAX_DIGITS] = {false};
    
    // 将数字转换为字符串
    while (num > 0) {
        digits[len++] = num % 10 + '0';
        num /= 10;
    }
    
    // 反转字符串
    for (int i = 0; i < len / 2; i++) {
        char temp = digits[i];
        digits[i] = digits[len - 1 - i];
        digits[len - 1 - i] = temp;
    }
    
    int pos = 0;
    for (int i = 0; i < len; i++) {
        if (digits[pos] == '0') return false;  // 不能包含0
        int step = digits[pos] - '0';
        if (visited[pos]) return false;  // 不能重复访问
        visited[pos] = true;
        pos = (pos + step) % len;
    }
    
    return (pos == 0) && (memchr(visited, false, len) == NULL);
}

int findNextRunaround(int m) {
    m++;
    while (!isRunaround(m)) {
        m++;
    }
    return m;
}

int main() {
    int m;
    scanf("%d", &m);
    printf("%d\n", findNextRunaround(m));
    return 0;
}