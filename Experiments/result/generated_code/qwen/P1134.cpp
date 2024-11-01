#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    long long factorial = 1;
    for (int i = 1; i <= n; ++i) {
        factorial *= i;
        while (factorial % 10 == 0) {
            factorial /= 10;
        }
        factorial %= 1000000000;
    }

    printf("%d\n", factorial);
    return 0;
}