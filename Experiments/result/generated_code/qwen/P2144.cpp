#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    if (n == 1) {
        printf("1\n");
    } else {
        long long result = 1;
        for (int i = 2; i <= n; i++) {
            result = result * i * (i - 1) / 2;
        }
        printf("%lld\n", result);
    }
    return 0;
}