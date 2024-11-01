#include <stdio.h>

char* battle(long long n, long long m, long long p) {
    if (m % p == 0) return "Alice";
    if (n % p == 0) return "Bob";
    
    long long alice_moves = n / p;
    long long bob_moves = (m - 1) / p + 1;
    
    if (alice_moves < bob_moves) return "Bob";
    if (alice_moves > bob_moves) return "Alice";
    return "Lasting Battle";
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        long long n, m, p;
        scanf("%lld %lld %lld", &n, &m, &p);
        printf("%s\n", battle(n, m, p));
    }
    
    return 0;
}