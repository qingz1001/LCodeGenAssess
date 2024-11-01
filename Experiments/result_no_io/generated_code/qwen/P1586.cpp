#include <stdio.h>

int count_ways(int n) {
    int count = 0;
    for (int i = 0; i <= n / 16; i++) {
        for (int j = 0; j <= n / 9; j++) {
            for (int k = 0; k <= n / 4; k++) {
                int l = n - (i * i + j * j + k * k);
                if (l >= 0 && l % 1 == 0) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", count_ways(n));
    }
    return 0;
}