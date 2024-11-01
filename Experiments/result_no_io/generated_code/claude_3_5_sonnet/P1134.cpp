#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
        while (result % 10 == 0) {
            result /= 10;
        }
        result %= 10;
    }

    printf("%d\n", result);
    return 0;
}