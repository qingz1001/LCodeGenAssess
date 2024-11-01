#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    int sqrt_n = sqrt(n);
    for (int i = 2; i <= sqrt_n; i++) {
        if (n % i == 0) {
            printf("%d\n", n / i);
            return 0;
        }
    }
    printf("%d\n", n);
    return 0;
}