#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_A 20000000

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int n, i;
    long long cost = 0;
    int seq[MAX_N];

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &seq[i]);
    }

    for (i = 0; i < n - 1; i++) {
        int g = gcd(seq[i], seq[i+1]);
        while (g > 1) {
            cost += g;
            seq[i] /= g;
            seq[i+1] /= g;
            g = gcd(seq[i], seq[i+1]);
        }
    }

    printf("%lld\n", cost);

    return 0;
}