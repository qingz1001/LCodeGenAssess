#include <stdio.h>

int main() {
    int a, num = 37 * a;
    int digit = num % 10;  // 取最低位
    num /= 10;  // 去掉最低位

    while (num > 0) {
        if (num % 10 != digit) {
            printf("No\n");
            return 0;
        }
        num /= 10;  // 去掉最低位
    }

    printf("Yes\n");
    return 0;
}