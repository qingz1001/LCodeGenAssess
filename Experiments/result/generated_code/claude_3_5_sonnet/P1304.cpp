#include <stdio.h>
#include <stdbool.h>

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 4; i <= N; i += 2) {
        for (int j = 2; j <= i / 2; j++) {
            if (isPrime(j) && isPrime(i - j)) {
                printf("%d=%d+%d\n", i, j, i - j);
                break;
            }
        }
    }

    return 0;
}