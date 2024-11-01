#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX 1000000

void sieve(bool isPrime[], int limit) {
    for (int i = 2; i <= limit; i++) {
        isPrime[i] = true;
    }
    for (int i = 2; i * i <= limit; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

int countPrimesInRange(int L, int R) {
    int limit = (int)sqrt(R);
    bool isPrime[limit + 1];
    sieve(isPrime, limit);

    bool isPrimeRange[R - L + 1];
    for (int i = 0; i <= R - L; i++) {
        isPrimeRange[i] = true;
    }

    for (int i = 2; i <= limit; i++) {
        if (isPrime[i]) {
            int start = (L / i) * i;
            if (start < L) start += i;
            if (start == i) start += i;
            for (int j = start; j <= R; j += i) {
                isPrimeRange[j - L] = false;
            }
        }
    }

    int count = 0;
    for (int i = 0; i <= R - L; i++) {
        if (isPrimeRange[i]) {
            count++;
        }
    }
    return count;
}

int main() {
    int L, R;
    scanf("%d %d", &L, &R);
    printf("%d\n", countPrimesInRange(L, R));
    return 0;
}