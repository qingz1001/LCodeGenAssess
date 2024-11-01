#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void find_primes_sum(int n) {
    for (int i = 2; i <= n / 3; i++) {
        if (!is_prime(i)) continue;
        for (int j = i; j <= (n - i) / 2; j++) {
            if (!is_prime(j)) continue;
            int k = n - i - j;
            if (k > j && is_prime(k)) {
                printf("%d %d %d\n", i, j, k);
                return;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    find_primes_sum(n);
    return 0;
}