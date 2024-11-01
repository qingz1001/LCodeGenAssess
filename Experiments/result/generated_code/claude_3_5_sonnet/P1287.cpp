#include <stdio.h>

int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

int stirling(int n, int k) {
    if (n == k) return 1;
    if (k == 1) return 1;
    return stirling(n - 1, k - 1) + k * stirling(n - 1, k);
}

int main() {
    int n, r;
    scanf("%d %d", &n, &r);

    if (r > n || r == 0) {
        printf("0\n");
        return 0;
    }

    long long result = stirling(n, r) * factorial(r);
    printf("%lld\n", result);

    return 0;
}