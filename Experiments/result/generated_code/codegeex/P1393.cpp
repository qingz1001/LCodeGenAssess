#include <stdio.h>
#include <string.h>

#define MOD 998244353

int main() {
    int n, m, len_s;
    scanf("%d %d %d", &n, &m, &len_s);
    int s[len_s];
    for (int i = 0; i < len_s; i++) {
        scanf("%d", &s[i]);
    }

    // 计算总的组合数，即从 m 个按键中选 n 次的组合数
    long long total_combinations = 1;
    for (int i = 0; i < n; i++) {
        total_combinations = (total_combinations * m) % MOD;
    }

    // 计算包含名字 S 的组合数
    long long matching_combinations = 1;
    for (int i = 0; i < len_s; i++) {
        matching_combinations = (matching_combinations * s[i]) % MOD;
    }

    // 计算概率并取模
    long long probability = (matching_combinations * 1000000007) % MOD;
    probability = (probability * m) % MOD;
    probability = (probability * 1000000007) % MOD;
    probability = (probability * m) % MOD;

    printf("%lld\n", probability);

    return 0;
}