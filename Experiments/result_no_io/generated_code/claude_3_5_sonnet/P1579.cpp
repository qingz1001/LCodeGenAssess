#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 2; i <= n - 4; i++) {
        if (!isPrime(i)) continue;
        for (int j = 2; j <= n - i - 2; j++) {
            if (!isPrime(j)) continue;
            int k = n - i - j;
            if (isPrime(k)) {
                printf("%d %d %d\n", i, j, k);
                return 0;
            }
        }
    }

    return 0;
}