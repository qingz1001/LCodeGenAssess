#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

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

    long long total_ways = 1;
    for (int i = 1; i <= n - 1; ++i) {
        total_ways = (total_ways * 3) % p;
    }

    long long invalid_ways = 0;
    for (int i = 2; i <= n - 1; ++i) {
        for (int j = i + 1; j <= n - 1; ++j) {
            if (gcd(i, j) != 1) {
                invalid_ways += 2;
            }
        }
    }
    invalid_ways %= p;

    long long valid_ways = (total_ways - invalid_ways + p) % p;
    printf("%lld\n", valid_ways);

    return 0;
}