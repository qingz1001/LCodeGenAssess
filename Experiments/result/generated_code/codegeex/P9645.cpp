#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long x, y, z;
        scanf("%lld %lld %lld", &x, &y, &z);
        
        // 计算x + y和z的差值
        long long diff = (z - x + y) % y;
        
        // 如果差值为0，说明x + y和z本身就是同余关系，直接输出y
        if (diff == 0) {
            printf("%lld\n", y);
        }
        // 如果差值不为0，检查是否存在一个k使得x + y ≡ z (mod k)
        else {
            long long k = y;
            long long g = __gcd(y, diff);
            if (g == 1) {
                k = y * diff;
            } else {
                k = y * diff / g;
            }
            // 检查k是否满足k > x和k > z
            if (k > x && k > z) {
                printf("%lld\n", k);
            } else {
                printf("-1\n");
            }
        }
    }
    return 0;
}