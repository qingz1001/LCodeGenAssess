#include <stdio.h>

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);

    if (n == 5 || n == 6) {
        printf("1\n");
        return 0;
    }

    long long last = 1;
    for (int len = 1; ; ++len) {
        last = (last * n) % 1000000000000000000LL;
        if (last == 1 && len >= k) {
            printf("%d\n", len);
            return 0;
        }
    }
}