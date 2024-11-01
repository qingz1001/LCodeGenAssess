#include <stdio.h>

int main() {
    long long n;
    scanf("%lld", &n);

    long long count = 0;

    for (long long j = 0; j <= n / 2 && j % 2 == 0; j++) { // 金神石
        for (long long m = 0; m <= n - j && m <= 9; m++) { // 木神石
            for (long long w = 0; w <= n - j - m && w <= 5; w++) { // 水神石
                for (long long h = 0; h <= n - j - m - w && h % 4 == 0; h++) { // 火神石
                    for (long long t = 0; t <= n - j - m - w - h && t <= 7; t++) { // 土神石
                        if (j + m + w + h + t == n) {
                            count++;
                        }
                    }
                }
            }
        }
    }

    printf("%lld\n", count);

    return 0;
}