#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    // A_n = 2 * A_{n-1} + 1
    printf("%d\n", (1 << n) - 1);
    return 0;
}