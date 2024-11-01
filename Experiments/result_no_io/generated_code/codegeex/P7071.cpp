#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int i;
    for (i = 1; i <= n; i *= 2) {
        if (n % i != 0) {
            printf("-1\n");
            return 0;
        }
        n -= i;
    }

    for (i = 1; i <= n; i *= 2) {
        printf("%d ", i);
    }

    return 0;
}