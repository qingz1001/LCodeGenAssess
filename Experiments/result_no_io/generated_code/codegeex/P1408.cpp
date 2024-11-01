#include <stdio.h>
#include <math.h>

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

    int cost = 0;
    for (int i = 1; i < n; i++) {
        int g = gcd(a[i], a[i + 1]);
        if (g > 1) {
            a[i] /= g;
            a[i + 1] /= g;
            cost += g;
        }
    }

    printf("%d\n", cost);
    return 0;
}