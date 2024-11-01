#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reverse_number(int n) {
    int reversed = 0;
    while (n != 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return reversed;
}

int main() {
    int N;
    scanf("%d", &N);
    
    int reversed_N = reverse_number(N);
    printf("%d\n", reversed_N);
    
    return 0;
}