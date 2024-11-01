#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n, m, p;
        scanf("%lld %lld %lld", &n, &m, &p);
        
        // Alice's turn
        n -= n % p;
        if (n == 0) {
            printf("Alice\n");
            continue;
        }
        
        // Bob's turn
        m -= m % p;
        if (m == 0) {
            printf("Bob\n");
            continue;
        }
        
        // If both are still non-zero, it's a lasting battle
        printf("Lasting Battle\n");
    }
    return 0;
}