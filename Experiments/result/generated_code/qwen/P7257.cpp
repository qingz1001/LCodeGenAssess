#include <stdio.h>

int reverseNumber(int num) {
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
    
    int reversedA = reverseNumber(a);
    int reversedB = reverseNumber(b);
    
    if (reversedA > reversedB) {
        printf("%d\n", reversedA);
    } else {
        printf("%d\n", reversedB);
    }
    
    return 0;
}