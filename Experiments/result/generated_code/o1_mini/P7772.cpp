#include <stdio.h>

int main(){
    int A, I, N;
    scanf("%d %d", &A, &I);
    N = A * (I - 1) + 1;
    printf("%d\n", N);
    return 0;
}