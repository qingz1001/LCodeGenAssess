#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000000

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int n, p;
    scanf("%d %d", &n, &p);

    long long total = 1;
    for (int i = 1; i <= n - 1; ++i) {
        total = (total * 2) % p;
    }

    long long invalid = 0;
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = i + 1; j <= n - 1; ++j) {
            if (gcd(i + 1, j + 1) != 1) {
                invalid++;
            }
        }
    }

    invalid = (invalid * 2) % p;

    long long result = (total - invalid + p) % p;
    printf("%lld\n", result);

    return 0;
}