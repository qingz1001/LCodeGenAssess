#include <stdio.h>
#include <stdlib.h>

#define MAXN 2000000000

int prime[MAXN];
int g[MAXN];

void sieve(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!prime[i]) {
            prime[i] = 1;
            for (int j = i * 2; j <= n; j += i) {
                prime[j] = 2;
            }
        }
    }
}

void calculate_g(int n) {
    for (int i = 1; i <= n; ++i) {
        int p = prime[i];
        if (p == 1) {
            g[i] = g[i - 1] + 1;
        } else {
            g[i] = g[i - 1];
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);
    sieve(MAXN);
    calculate_g(MAXN);
    int max_reversed_prime = 1;
    for (int i = 2; i <= N; ++i) {
        if (g[i] > g[max_reversed_prime]) {
            max_reversed_prime = i;
        }
    }
    printf("%d\n", max_reversed_prime);
    return 0;
}