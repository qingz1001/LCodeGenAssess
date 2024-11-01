#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n, m, p;
        scanf("%lld %lld %lld", &n, &m, &p);
        
        // 分析：
        // 如果 n % p == 0，Alice 会在第一次操作中将 m 减到 0，Alice 获胜。
        // 如果 m % p == 0，Bob 会在第一次操作中将 n 减到 0，Bob 获胜。
        // 如果 n % p != 0 且 m % p != 0，我们需要检查 (n - n % p) % p 和 (m - m % p) % p 是否相等。
        // 如果相等，则游戏会平局；如果不相等，则 Alice 或 Bob 会获胜。
        
        if (n % p == 0) {
            printf("Alice\n");
        } else if (m % p == 0) {
            printf("Bob\n");
        } else if ((n - n % p) % p == (m - m % p) % p) {
            printf("Lasting Battle\n");
        } else {
            printf("Alice\n");
        }
    }
    return 0;
}