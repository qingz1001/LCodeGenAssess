#include <stdio.h>
#include <stdbool.h>

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void generateSpecialPrimes(int n) {
    int numbers[] = {2, 3, 5, 7};
    int count = 4;

    while (count > 0) {
        int newCount = 0;
        for (int i = 0; i < count; i++) {
            int num = numbers[i];
            for (int digit = 1; digit <= 9; digit += 2) {
                int nextNum = num * 10 + digit;
                if (isPrime(nextNum)) {
                    numbers[newCount++] = nextNum;
                }
            }
        }
        count = newCount;
    }

    for (int i = 0; i < count; i++) {
        int num = numbers[i];
        bool special = true;
        for (int len = n; len >= 1; len--) {
            if (!isPrime(num % (int)pow(10, len))) {
                special = false;
                break;
            }
        }
        if (special) {
            printf("%d\n", num);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    generateSpecialPrimes(n);
    return 0;
}