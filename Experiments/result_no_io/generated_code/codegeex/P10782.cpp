#include <stdio.h>

int main() {
    long long T, a, c;
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld%lld", &a, &c);
        if (c == 0) {
            printf("-1\n");
        } else {
            long long n = a / c;
            long long m = a / n;
            if (m != c) {
                printf("-1\n");
            } else {
                printf("%lld\n", n);
            }
        }
    }
    return 0;
}