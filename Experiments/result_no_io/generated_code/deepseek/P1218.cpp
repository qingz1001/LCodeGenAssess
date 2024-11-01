#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

void generate_special_primes(int n, int current, int length) {
    if (length == n) {
        printf("%d\n", current);
        return;
    }
    for (int i = 1; i <= 9; i += 2) { // Only odd numbers can be prime (except 2)
        int next = current * 10 + i;
        if (is_prime(next)) {
            generate_special_primes(n, next, length + 1);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int start_primes[] = {2, 3, 5, 7}; // Starting primes for length 1
    for (int i = 0; i < 4; i++) {
        generate_special_primes(n, start_primes[i], 1);
    }
    return 0;
}