#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

bool isPrime(int num) {
    if (num < 2) return false;
    int sqrtNum = sqrt(num);
    for (int i = 2; i <= sqrtNum; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int L, R;
    scanf("%d %d", &L, &R);

    int count = 0;
    for (int i = L; i <= R; i++) {
        if (isPrime(i)) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}