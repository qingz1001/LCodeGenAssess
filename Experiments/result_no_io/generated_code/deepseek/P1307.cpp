#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char num[12]; // 最多10位数 + 负号 + 终止符
    scanf("%s", num);

    int len = strlen(num);
    int start = 0;
    int end = len - 1;

    // 处理负数的情况
    if (num[0] == '-') {
        printf("-");
        start = 1;
    }

    // 跳过末尾的零
    while (end >= start && num[end] == '0') {
        end--;
    }

    // 从后向前输出数字
    for (int i = end; i >= start; i--) {
        printf("%c", num[i]);
    }

    printf("\n");
    return 0;
}