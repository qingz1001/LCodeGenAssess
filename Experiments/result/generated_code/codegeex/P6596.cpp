#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

// Function to compute factorial modulo MOD
long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result = (result * i) % MOD;
    }
    return result;
}

// Function to compute binomial coefficient C(n, k) modulo MOD
long long binomial(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    long long numerator = 1, denominator = 1;
    for (int i = 0; i < k; i++) {
        numerator = (numerator * (n - i)) % MOD;
        denominator = (denominator * (i + 1)) % MOD;
    }
    return (numerator * binomial(n - k, k - 1) % MOD) * binomial(n - k, k - 1) % MOD;
}

// Function to compute the number of connected graphs with at most m cut edges
long long countGraphs(int n, int m) {
    long long result = 0;
    for (int i = 0; i <= m; i++) {
        result = (result + binomial(n - 1, i) * factorial(n - 1) % MOD) % MOD;
    }
    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    long long answer = countGraphs(n, m);
    printf("%lld\n", answer);
    return 0;
}