#include <stdio.h>
#include <algorithm>
#include <limits.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int n;
    scanf("%d", &n);
    int a[10001];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    int min_cost = 0;
    for (int i = 1; i < n; i++) {
        int g = gcd(a[i], a[i + 1]);
        if (g > 1) {
            min_cost += g;
            a[i + 1] /= g;
        }
    }

    printf("%d\n", min_cost);
    return 0;
}