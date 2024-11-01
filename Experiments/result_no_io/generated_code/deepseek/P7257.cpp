#include <stdio.h>

int reverse_number(int num) {
    int reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    int reversed_a = reverse_number(a);
    int reversed_b = reverse_number(b);
    
    if (reversed_a > reversed_b) {
        printf("%d\n", reversed_a);
    } else {
        printf("%d\n", reversed_b);
    }
    
    return 0;
}