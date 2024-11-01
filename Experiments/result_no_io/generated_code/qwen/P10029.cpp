#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n, m, p;
        scanf("%lld %lld %lld", &n, &m, &p);
        
        if (n % p == 0) {
            printf("Bob\n");
        } else if (m % p == 0) {
            printf("Alice\n");
        } else {
            printf("Lasting Battle\n");
        }
    }
    return 0;
}