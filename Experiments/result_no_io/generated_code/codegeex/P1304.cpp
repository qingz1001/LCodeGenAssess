#include <stdio.h>

int isPrime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
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