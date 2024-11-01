#include <stdio.h>

typedef long long ll;

ll n, k, m, p;
ll ans;

int main() {
    scanf("%lld%lld%lld%lld", &n, &k, &m, &p);
    
    // 初始化答案为1
    ans = 1;
    
    // 循环k-1次，计算每一天的价格差的可能种数
    for (int i = 1; i < k; i++) {
        // 计算每一天的价格差的可能种数
        ans = (ans * (m + 1)) % p;
    }
    
    // 输出结果
    printf("%lld\n", ans);
    
    return 0;
}