#include <stdio.h>

int main() {
    int k;
    scanf("%d", &k);
    double S = 0.0;
    int n = 0;
    while (S <= k) {
        n++;
        S += 1.0 / n;
    }
    printf("%d\n", n);
    return 0;
}