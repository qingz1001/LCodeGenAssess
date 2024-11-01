#include <stdio.h>
#include <stdbool.h>

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void generateSuperprimes(int n, int num, int digit) {
    if (digit == n) {
        printf("%d\n", num);
        return;
    }
    
    for (int i = 1; i <= 9; i += 2) {  // 只考虑奇数，因为偶数不可能是质数（除了2）
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