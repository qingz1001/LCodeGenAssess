#include <stdio.h>

int main() {
    long long n;
    scanf("%lld", &n);
    int m = 0;
    while (n > 1) {
        n /= 2;
        m++;
    }
    if (n % 2 == 0) {
        printf("%d\n", m);
    } else {
        printf("%d\n", m - 1);
    }
    return 0;
}