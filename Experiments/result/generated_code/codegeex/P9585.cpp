#include <stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    if (n <= m / 2) {
        printf("%d\n", 2 * n);
    } else {
        printf("%d\n", 2 * n - (m - n));
    }

    return 0;
}