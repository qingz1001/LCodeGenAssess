#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 2; i < n; i++) {
        if (is_prime(i)) {
            for (int j = i; j < n; j++) {
                if (is_prime(j)) {
                    int k = n - i - j;
                    if (k >= j && is_prime(k)) {
                        printf("%d %d %d\n", i, j, k);
                        return 0;
                    }
                }
            }
        }
    }

    return 0;
}