#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int solve(int n, int m) {
    if (n < 2 || m < 2) return 0;
    if (n == 2 && m == 2) return 0;
    if (n == 2) return m / 3;
    if (m == 2) return n / 3;
    return (n * m) / 3;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    printf("%d\n", solve(n, m));
    return 0;
}