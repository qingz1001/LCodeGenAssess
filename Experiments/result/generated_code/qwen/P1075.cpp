#include <stdio.h>

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            printf("%d\n", n / i > i ? n / i : i);
            return 0;
        }
    }
    printf("%d\n", n);
    return 0;
}