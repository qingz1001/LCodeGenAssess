#include <stdio.h>
#include <stdbool.h>

#define MAX 10000

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void goldbachConjecture(int N) {
    for (int i = 2; i <= N / 2; i++) {
        int even = 2 * i;
        for (int j = 2; j <= even / 2; j++) {
            if (isPrime(j) && isPrime(even - j)) {
                printf("%d=%d+%d\n", even, j, even - j);
                break;
            }
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);
    goldbachConjecture(N);
    return 0;
}