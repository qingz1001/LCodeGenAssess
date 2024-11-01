#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n, m, p;
        scanf("%lld %lld %lld", &n, &m, &p);
        
        // 分析：
        // 如果 n 或 m 本身就是 p 的倍数，那么在第一次操作后，它们的值会变为 0，所以 Alice 或 Bob 会立即获胜。
        // 否则，考虑 n 和 m 分别对 p 取模的结果：
        // 如果 n % p == m % p，那么每次操作后，n 和 m 的变化量相同，游戏会无限进行，最终平局。
        // 如果 n % p != m % p，那么在游戏开始时，Alice 或 Bob 一定可以通过一次操作使得 n 或 m 变为 0，Alice 会获胜。
        
        if (n % p == 0 || m % p == 0) {
            printf("Alice\n");
        } else if (n % p == m % p) {
            printf("Lasting Battle\n");
        } else {
            printf("Alice\n");
        }
    }
    return 0;
}