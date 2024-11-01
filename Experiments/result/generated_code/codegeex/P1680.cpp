#include <stdio.h>

#define MOD 1000000007

long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result = (result * i) % MOD;
    }
    return result;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int C[1000000];
    for (int i = 0; i < M; i++) {
        scanf("%d", &C[i]);
    }

    // 计算总的分组方案数
    long long totalWays = factorial(N);
    for (int i = 0; i < M; i++) {
        totalWays = (totalWays * factorial(N - C[i])) % MOD;
        N -= C[i];
    }

    // 计算每个组的方案数
    for (int i = 0; i < M; i++) {
        totalWays = (totalWays * factorial(N - 1)) % MOD;
        N--;
    }

    printf("%lld\n", totalWays);
    return 0;
}