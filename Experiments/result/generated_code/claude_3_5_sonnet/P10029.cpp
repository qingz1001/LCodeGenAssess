#include <stdio.h>

void solve() {
    long long n, m, p;
    scanf("%lld %lld %lld", &n, &m, &p);
    
    if (m % p == 0) {
        printf("Alice\n");
    } else if (n % p == 0) {
        printf("Bob\n");
    } else {
        long long an = n % p;
        long long bm = m % p;
        
        if (an < bm) {
            printf("Bob\n");
        } else if (an > bm) {
            printf("Alice\n");
        } else {
            printf("Lasting Battle\n");
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        solve();
    }
    
    return 0;
}