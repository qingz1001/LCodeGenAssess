#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d\n", gcd(n, k));
    return 0;
}