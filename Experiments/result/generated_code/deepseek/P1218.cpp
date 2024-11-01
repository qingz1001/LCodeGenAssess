#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

void findSpecialPrimes(int n, int current, int length) {
    if (length == n) {
        printf("%d\n", current);
        return;
    }
    for (int i = 1; i <= 9; i += 2) { // Only odd numbers can be prime (except 2)
        int next = current * 10 + i;
        if (isPrime(next)) {
            findSpecialPrimes(n, next, length + 1);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    // Start with the single-digit primes
    int startPrimes[] = {2, 3, 5, 7};
    for (int i = 0; i < 4; i++) {
        findSpecialPrimes(n, startPrimes[i], 1);
    }
    
    return 0;
}