#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    long long factorial = 1;
    for (int i = 1; i <= N; i++) {
        factorial *= i;
        while (factorial % 10 == 0) {
            factorial /= 10;
        }
        factorial %= 1000000000; // To prevent overflow
    }

    printf("%lld\n", factorial);
    return 0;
}