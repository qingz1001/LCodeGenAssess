#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int count_primes_in_range(int L, int R) {
    int count = 0;
    for (int i = L; i <= R; i++) {
        if (is_prime(i)) {
            count++;
        }
    }
    return count;
}

int main() {
    int L, R;
    scanf("%d %d", &L, &R);
    printf("%d\n", count_primes_in_range(L, R));
    return 0;
}