#include <stdio.h>

int main() {
    int A, I;
    scanf("%d %d", &A, &I);
    
    int N = A * (I - 1) + 1;
    
    printf("%d\n", N);
    
    return 0;
}