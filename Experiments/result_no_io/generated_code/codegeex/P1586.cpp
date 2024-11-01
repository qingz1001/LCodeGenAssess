#include <stdio.h>
#include <math.h>

int fourSquares(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (n == 1) return 1;
    if (n == 2) return 2;
    if (n == 3) return 3;
    if (n == 4) return 1;

    int count = 0;
    for (int i = 1; i * i <= n; i++) {
        for (int j = i; j * j <= n - i * i; j++) {
            for (int k = j; k * k <= n - i * i - j * j; k++) {
                int l = (int)sqrt(n - i * i - j * j - k * k);
                if (l * l == n - i * i - j * j - k * k) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", fourSquares(n));
    }
    return 0;
}