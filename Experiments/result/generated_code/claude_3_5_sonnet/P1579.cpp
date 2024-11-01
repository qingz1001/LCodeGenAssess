#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 2; i <= n; i++) {
        if (!isPrime(i)) continue;
        for (int j = i; j <= n; j++) {
            if (!isPrime(j)) continue;
            int k = n - i - j;
            if (k >= j && isPrime(k)) {
                printf("%d %d %d\n", i, j, k);
                return 0;
            }
        }
    }

    return 0;
}