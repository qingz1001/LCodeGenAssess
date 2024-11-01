#include <stdio.h>
#include <string.h>

int main() {
    int M;
    char N[1001];
    scanf("%d %s", &M, N);

    int len = strlen(N);
    int firstNonZero = -1;

    // 找到第一个非零位
    for (int i = 0; i < len; i++) {
        if (N[i] != '0') {
            firstNonZero = i;
            break;
        }
    }

    // 如果所有位都是0
    if (firstNonZero == -1) {
        printf("0");
        return 0;
    }

    // 打印第一个非零位
    printf("%c * %d^%d", N[firstNonZero], M, firstNonZero);

    // 打印剩余的项
    for (int i = firstNonZero + 1; i < len; i++) {
        if (N[i] != '0') {
            printf(" + %c * %d^%d", N[i], M, i);
        }
    }

    return 0;
}