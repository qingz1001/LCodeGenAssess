#include <stdio.h>

long long solve(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    return (n - 1) * (solve(n - 1) + solve(n - 2));
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", solve(n));
    return 0;
}