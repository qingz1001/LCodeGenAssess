#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

void goldbach_conjecture(int N) {
    for (int i = 2; i <= N / 2; i++) {
        int even = 2 * i;
        for (int j = 2; j <= even / 2; j++) {
            if (is_prime(j) && is_prime(even - j)) {
                printf("%d=%d+%d\n", even, j, even - j);
                break;
            }
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);
    goldbach_conjecture(N);
    return 0;
}