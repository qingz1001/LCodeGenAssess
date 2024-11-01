#include <stdio.h>
#include <stdbool.h>

bool containsSeven(int num) {
    while (num > 0) {
        if (num % 10 == 7) return true;
        num /= 10;
    }
    return false;
}

int main() {
    int X;
    scanf("%d", &X);
    
    int n = 1337;
    int direction = 1; // 1 for forward, -1 for backward
    
    while (n != X) {
        n += direction;
        if (n > 1337) {
            n = 1;
        } else if (n <= 0) {
            n = 1337;
        }
        
        if (n % 7 == 0 || containsSeven(n)) {
            direction *= -1;
        }
    }
    
    printf("%d\n", n);
    
    return 0;
}