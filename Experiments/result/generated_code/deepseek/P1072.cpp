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

// 计算最小公倍数
int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int a0, a1, b0, b1;
        scanf("%d %d %d %d", &a0, &a1, &b0, &b1);

        int count = 0;
        for (int x = 1; x * x <= b1; x++) {
            if (b1 % x == 0) {
                if (gcd(x, a0) == a1 && lcm(x, b0) == b1) {
                    count++;
                }
                int y = b1 / x;
                if (y != x && gcd(y, a0) == a1 && lcm(y, b0) == b1) {
                    count++;
                }
            }
        }
        printf("%d\n", count);
    }
    return 0;
}