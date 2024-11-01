#include <stdio.h>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int solve(int a0, int a1, int b0, int b1) {
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
    return count;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int a0, a1, b0, b1;
        scanf("%d %d %d %d", &a0, &a1, &b0, &b1);
        printf("%d\n", solve(a0, a1, b0, b1));
    }
    return 0;
}