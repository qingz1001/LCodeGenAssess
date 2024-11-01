#include <stdio.h>

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    int is_prime[n + 1];
    for (int i = 2; i <= n; i++) {
        is_prime[i] = 1;
    }

    int count = 0;
    for (int p = 2; p * p <= n; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p) {
                if (is_prime[i]) {
                    count++;
                    if (count == k) {
                        printf("%d\n", i);
                        return 0;
                    }
                    is_prime[i] = 0;
                }
            }
        }
    }

    for (int i = n; i >= 2; i--) {
        if (is_prime[i]) {
            count++;
            if (count == k) {
                printf("%d\n", i);
                return 0;
            }
        }
    }

    return 0;
}