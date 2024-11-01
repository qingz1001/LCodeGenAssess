#include <stdio.h>

// 计算最大公约数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 判断分数是否为纯循环小数
int isPureCircular(int x, int y, int k) {
    int g = gcd(x, y);
    x /= g;
    y /= g;
    while (y % k == 0) {
        y /= k;
    }
    return gcd(y, k) == 1;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int count = 0;
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            if (isPureCircular(x, y, k)) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}