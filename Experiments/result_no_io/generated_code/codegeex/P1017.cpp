#include <stdio.h>

// 将十进制数转换为负进制数
void convertToNegativeBase(int n, int R) {
    if (n == 0) {
        printf("0");
        return;
    }

    char digits[] = "0123456789ABCDEF";
    int sign = 1;
    if (n < 0) {
        sign = -1;
        n = -n;
    }

    char result[100];
    int index = 0;

    while (n != 0) {
        int remainder = n % R;
        result[index++] = digits[-remainder];
        n /= R;
    }

    if (sign == -1) {
        result[index++] = '-';
    }

    for (int i = index - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
}

int main() {
    int n, R;
    while (scanf("%d %d", &n, &R) != EOF) {
        convertToNegativeBase(n, R);
        printf("\n");
    }
    return 0;
}