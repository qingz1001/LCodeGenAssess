#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int C;
    scanf("%d", &C);
    while (C--) {
        int M, N;
        scanf("%d %d", &M, &N);
        if (gcd(M, N) == 1) {
            printf("Stan wins\n");
        } else {
            printf("Ollie wins\n");
        }
    }
    return 0;
}