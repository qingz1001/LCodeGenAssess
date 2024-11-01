#include <stdio.h>

int count_ways(int n) {
    int count = 0;
    for (int i = 0; i * i <= n; i++) {
        for (int j = i; j * j <= n - i * i; j++) {
            for (int k = j; k * k <= n - i * i - j * j; k++) {
                int l = sqrt(n - i * i - j * j - k * k);
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
        printf("%d\n", count_ways(n));
    }
    return 0;
}