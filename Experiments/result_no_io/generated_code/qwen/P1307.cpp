#include <stdio.h>

int main() {
    int N, reversed = 0;
    scanf("%d", &N);

    if (N == 0) {
        printf("0\n");
        return 0;
    }

    while (N != 0) {
        int digit = N % 10;
        reversed = reversed * 10 + digit;
        N /= 10;
    }

    printf("%d\n", reversed);
    return 0;
}