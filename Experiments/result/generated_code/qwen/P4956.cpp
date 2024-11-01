#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int max_x = 100;
    int min_k = 1;

    for (int x = 100; x >= 1; x--) {
        for (int k = 1; k <= 100; k++) {
            int total = 0;
            for (int i = 0; i < 52; i++) {
                total += x + i * k;
            }
            if (total == n) {
                printf("%d\n%d\n", x, k);
                return 0;
            }
        }
    }

    return 0;
}