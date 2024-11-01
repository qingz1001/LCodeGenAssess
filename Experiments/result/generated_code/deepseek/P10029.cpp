#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n, m, p;
        scanf("%lld %lld %lld", &n, &m, &p);
        
        if (p == 1) {
            // If p is 1, the game will always result in a draw
            printf("Lasting Battle\n");
        } else {
            // Calculate the number of operations needed for Alice and Bob
            long long alice_ops = (n + p - 1) / p; // ceil(n / p)
            long long bob_ops = (m + p - 1) / p;   // ceil(m / p)
            
            if (alice_ops <= bob_ops) {
                printf("Alice\n");
            } else {
                printf("Bob\n");
            }
        }
    }
    return 0;
}