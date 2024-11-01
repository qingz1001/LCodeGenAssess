#include <stdio.h>
#include <stdbool.h>

#define MAX_P 100005

bool isPrime[MAX_P];
int primes[MAX_P];
int primeCount = 0;

void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        isPrime[i] = true;
    }
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes[primeCount++] = i;
            for (int j = i * 2; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

long long euler_phi(long long n) {
    long long result = n;
    for (int i = 0; i < primeCount && primes[i] * primes[i] <= n; i++) {
        if (n % primes[i] == 0) {
            while (n % primes[i] == 0) {
                n /= primes[i];
            }
            result -= result / primes[i];
        }
    }
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

long long find_min_x(int m, int p[], int q[]) {
    long long x = 0;
    bool has_two = false;
    for (int i = 0; i < m; i++) {
        if (p[i] == 2) {
            has_two = true;
        }
        x += (p[i] - 1) * q[i];
    }
    if (!has_two) {
        x++;
    }
    return x;
}

int main() {
    sieve(MAX_P - 1);
    int test;
    scanf("%d", &test);
    while (test--) {
        int m;
        scanf("%d", &m);
        int p[m], q[m];
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &p[i], &q[i]);
        }
        printf("%lld\n", find_min_x(m, p, q));
    }
    return 0;
}