#include <stdio.h>

int main() {
    int A, I;
    scanf("%d %d", &A, &I);
    int N = (I - 1) * A + 1;
    printf("%d\n", N);
    return 0;
}