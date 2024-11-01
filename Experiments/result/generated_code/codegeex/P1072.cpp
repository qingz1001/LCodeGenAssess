#include <stdio.h>
#include <math.h>

// 求最大公约数
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// 求最小公倍数
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main() {
    int n;
    scanf("%d", &n);

    while (n--) {
        int a0, a1, b0, b1;
        scanf("%d%d%d%d", &a0, &a1, &b0, &b1);

        int count = 0;
        // 枚举所有可能的x
        for (int x = 1; x * a1 <= a0; x++) {
            if (gcd(x * a1, a0) == a1 && lcm(x * a1, b0) == b1) {
                count++;
            }
        }

        printf("%d\n", count);
    }

    return 0;
}