#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    // 每个数字需要的星号数量
    int digit_stars[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

    // 计算最大能拼出的数字
    int max_digit = 0;
    while (n >= digit_stars[max_digit]) {
        n -= digit_stars[max_digit];
        max_digit++;
    }

    printf("%d\n", max_digit);

    return 0;
}