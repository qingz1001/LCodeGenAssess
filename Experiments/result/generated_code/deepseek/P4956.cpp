#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    for (int k = 1; ; k++) {
        for (int x = 100; x > 0; x--) {
            int total = 52 * (7 * x + 21 * k);
            if (total == n) {
                printf("%d\n%d\n", x, k);
                return 0;
            }
        }
    }

    return 0;
}