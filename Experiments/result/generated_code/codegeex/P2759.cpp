#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    double x = log(n) / log(10);
    x = ceil(x);
    x = pow(10, x);

    printf("%d\n", (int)x);

    return 0;
}