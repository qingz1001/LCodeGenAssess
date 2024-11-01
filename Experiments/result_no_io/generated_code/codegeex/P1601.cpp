#include <stdio.h>
#include <string.h>

#define MAX_LEN 501

int main() {
    char a[MAX_LEN], b[MAX_LEN];
    int result[MAX_LEN] = {0};
    int carry = 0;

    // 读取输入
    scanf("%s", a);
    scanf("%s", b);

    // 将字符串转换为整数并进行高精度加法
    for (int i = MAX_LEN - 1; i >= 0; i--) {
        int sum = carry;
        if (i < strlen(a)) {
            sum += a[strlen(a) - i - 1] - '0';
        }
        if (i < strlen(b)) {
            sum += b[strlen(b) - i - 1] - '0';
        }
        carry = sum / 10;
        result[i] = sum % 10;
    }

    // 找到结果的第一个非零位
    int start = 0;
    while (start < MAX_LEN && result[start] == 0) {
        start++;
    }

    // 输出结果
    if (start == MAX_LEN) {
        printf("0\n");
    } else {
        for (int i = start; i < MAX_LEN; i++) {
            printf("%d", result[i]);
        }
        printf("\n");
    }

    return 0;
}