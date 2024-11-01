#include <stdio.h>

int main() {
    int N, K;
    scanf("%d%d", &N, &K);
    
    int p[K];
    for (int i = 0; i < K; i++) {
        scanf("%d", &p[i]);
    }
    
    int c[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);
    }
    
    // 检查是否严格递增
    for (int i = 0; i < N - 1; i++) {
        if (c[i] >= c[i + 1]) {
            printf("impossible\n");
            return 0;
        }
    }
    
    // 计算最大天数
    int max_days = 0;
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (count < K && i + 1 == p[count]) {
            count++;
        }
        max_days++;
    }
    
    printf("%d\n", max_days);
    return 0;
}