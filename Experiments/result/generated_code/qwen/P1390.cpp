#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long sum_of_gcd(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            sum += gcd(i, j);
        }
    }
    return sum;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", sum_of_gcd(n));
    return 0;
}