#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

long long count_x(int a0, int a1, int b0, int b1) {
    if (lcm(a1, b0) > b1) return 0;
    int g = gcd(a0, b0);
    int l = lcm(a1, b0);
    int k = b1 / l;
    return (long long)k * g;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a0, a1, b0, b1;
        scanf("%d %d %d %d", &a0, &a1, &b0, &b1);
        printf("%lld\n", count_x(a0, a1, b0, b1));
    }
    return 0;
}