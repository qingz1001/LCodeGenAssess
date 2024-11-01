#include <stdio.h>

int main() {
    int k, n = 0;
    double S = 0.0;

    scanf("%d", &k);

    while (S <= k) {
        n++;
        S += 1.0 / n;
    }

    printf("%d\n", n);

    return 0;
}