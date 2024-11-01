#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n, m, p;
        scanf("%lld %lld %lld", &n, &m, &p);
        if (n == 0) {
            printf("Bob\n");
        } else if (m == 0) {
            printf("Alice\n");
        } else {
            long long gcd = __gcd(n, p);
            if (m % gcd != 0) {
                printf("Alice\n");
            } else {
                printf("Bob\n");
            }
        }
    }
    return 0;
}