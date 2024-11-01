#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    // 判断输入的星号数量是否能拼出1, 2, 3, 4, 5, 6, 7, 8, 9
    if (n >= 5) {
        printf("9");
        n -= 5;
    }
    if (n >= 4) {
        printf("8");
        n -= 4;
    }
    if (n >= 7) {
        printf("7");
        n -= 7;
    }
    if (n >= 5) {
        printf("6");
        n -= 5;
    }
    if (n >= 5) {
        printf("5");
        n -= 5;
    }
    if (n >= 4) {
        printf("4");
        n -= 4;
    }
    if (n >= 5) {
        printf("3");
        n -= 5;
    }
    if (n >= 4) {
        printf("2");
        n -= 4;
    }
    if (n >= 5) {
        printf("1");
    }

    return 0;
}