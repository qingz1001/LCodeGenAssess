#include <stdio.h>

// 计算最大公约数
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    int a, b;
    scanf("%d%d", &a, &b);

    // 确保 a < b
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // 计算差值
    int diff = b - a;

    // 计算最大公约数
    int g = gcd(a, diff);

    // 判断是否为必败态
    if (g == a) {
        printf("0\n"); // 必败态
    } else {
        printf("1\n"); // 必胜态
    }

    return 0;
}