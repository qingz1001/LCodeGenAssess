#include <stdio.h>

int main() {
    int n, r;
    scanf("%d %d", &n, &r);
    if (r == 0) {
        printf("0\n");
        return 0;
    }
    long long result = 1;
    for (int i = 0; i < r; ++i) {
        result *= (n - i);
    }
    printf("%lld\n", result);
    return 0;
}