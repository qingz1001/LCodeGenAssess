#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);

    int reversed = 0;
    int sign = 1;

    if (N < 0) {
        sign = -1;
        N = -N;
    }

    while (N > 0) {
        reversed = reversed * 10 + N % 10;
        N /= 10;
    }

    printf("%d\n", sign * reversed);

    return 0;
}