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
    int N;
    scanf("%d", &N);

    for (int i = 2; i <= N / 2; i++) {
        int num = i * 2;
        for (int j = 2; j <= num / 2; j++) {
            if (isPrime(j) && isPrime(num - j)) {
                printf("%d=%d+%d\n", num, j, num - j);
                break;
            }
        }
    }

    return 0;
}