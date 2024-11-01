#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void generateSuperprimes(int n, int num, int digit) {
    if (digit == n) {
        if (isPrime(num)) {
            printf("%d\n", num);
        }
        return;
    }
    
    for (int i = 1; i <= 9; i += 2) {
        int newNum = num * 10 + i;
        if (isPrime(newNum)) {
            generateSuperprimes(n, newNum, digit + 1);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    generateSuperprimes(n, 0, 0);
    
    return 0;
}