#include <stdio.h>

int containsSpecialDigit(int num) {
    while (num > 0) {
        int digit = num % 10;
        if (digit == 2 || digit == 0 || digit == 1 || digit == 9) {
            return 1;
        }
        num /= 10;
    }
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (containsSpecialDigit(i)) {
            sum += i;
        }
    }
    
    printf("%d\n", sum);
    return 0;
}