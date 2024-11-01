#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    double log_n = log10(n);
    int x = (int)ceil(log_n / (log10(x) + log10(x)));

    printf("%d\n", x);

    return 0;
}