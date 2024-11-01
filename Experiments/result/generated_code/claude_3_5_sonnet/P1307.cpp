#include <stdio.h>

int main() {
    int N, reversed = 0;
    scanf("%d", &N);
    
    int sign = (N < 0) ? -1 : 1;
    N = (N < 0) ? -N : N;
    
    while (N > 0) {
        reversed = reversed * 10 + N % 10;
        N /= 10;
    }
    
    printf("%d\n", sign * reversed);
    
    return 0;
}