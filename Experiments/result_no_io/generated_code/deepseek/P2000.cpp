#include <stdio.h>

int main() {
    char n[100001];
    scanf("%s", n);

    // 由于 n 非常大，直接计算不现实，我们只需要判断 n 的最后一位数字
    char last_digit = n[strlen(n) - 1];

    // 根据最后一位数字来判断大阵的种数
    int result;
    switch (last_digit) {
        case '0': case '2': case '4': case '6': case '8':
            result = 20;
            break;
        case '1': case '3': case '5': case '7': case '9':
            result = 20;
            break;
        default:
            result = 0;
            break;
    }

    printf("%d\n", result);
    return 0;
}