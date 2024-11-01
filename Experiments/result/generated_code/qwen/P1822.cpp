#include <stdio.h>
#include <stdlib.h>

int magic(int n) {
    if (n < 10) return n;
    int next = 0;
    while (n >= 10) {
        int digit1 = n % 10;
        n /= 10;
        int digit2 = n % 10;
        next = next * 10 + abs(digit1 - digit2);
    }
    return magic(next);
}

int main() {
    int A, B;
    scanf("%d%d", &A, &B);
    int count = 0;
    for (int i = A; i <= B; i++) {
        if (magic(i) == 7) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}