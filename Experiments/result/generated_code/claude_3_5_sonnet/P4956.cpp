#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    for (int x = 100; x >= 1; x--) {
        for (int k = 1; k <= 100; k++) {
            long long sum = 0;
            for (int i = 0; i < 7; i++) {
                sum += (x + i * k) * 52;
            }
            if (sum == n) {
                printf("%d\n%d\n", x, k);
                return 0;
            }
        }
    }

    return 0;
}