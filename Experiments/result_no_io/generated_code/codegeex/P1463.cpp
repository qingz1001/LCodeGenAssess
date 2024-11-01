#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

int primes[MAX], numofprimes;
int primecount[MAX];
int prime[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void sieve() {
    int i, j;
    for (i = 2; i < MAX; i++) {
        if (!primecount[i]) {
            primes[numofprimes++] = i;
            for (j = i; j < MAX; j += i) {
                primecount[j]++;
            }
        }
    }
}

int main() {
    sieve();
    long long n, i, j, k, l, max, maxcount;
    scanf("%lld", &n);
    max = 0;
    maxcount = 0;
    for (i = 0; i < numofprimes; i++) {
        for (j = 0; j < numofprimes && primes[i] * primes[j] <= n; j++) {
            for (k = 0; k < numofprimes && primes[i] * primes[j] * primes[k] <= n; k++) {
                for (l = 0; l < numofprimes && primes[i] * primes[j] * primes[k] * primes[l] <= n; l++) {
                    long long x = primes[i] * primes[j] * primes[k] * primes[l];
                    if (x > max || (x == max && primecount[x] > maxcount)) {
                        max = x;
                        maxcount = primecount[x];
                    }
                }
            }
        }
    }
    printf("%lld\n", max);
    return 0;
}