#include <stdio.h>

int main() {
    int N, S;
    scanf("%d%d", &N, &S);
    
    int C[N], Y[N];
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &C[i], &Y[i]);
    }
    
    long long total_cost = 0;
    
    for (int i = 0; i < N; i++) {
        int min_cost = C[i]; // 初始假设当前周生产机器的成本最低
        for (int j = 0; j < i; j++) {
            // 计算保养机器的成本
            int maintain_cost = C[j] + (i - j) * S;
            // 更新最低成本
            if (maintain_cost < min_cost) {
                min_cost = maintain_cost;
            }
        }
        // 累加总成本
        total_cost += min_cost * Y[i];
    }
    
    printf("%lld\n", total_cost);
    return 0;
}