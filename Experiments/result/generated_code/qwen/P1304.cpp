#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void find_prime_sum(int n) {
    for (int i = 2; i <= n / 2; i++) {
        int j = n - i;
        if (is_prime(i) && is_prime(j)) {
            printf("%d=%d+%d\n", n, i, j);
            break;
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= (N - 2) / 2; i++) {
        find_prime_sum(2 * i + 2);
    }
    return 0;
}