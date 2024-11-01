#include <stdio.h>

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    
    long long square_count = 0;
    long long rectangle_count = 0;
    
    // 计算正方形的个数
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (i == j) {
                square_count += i * j;
            } else {
                square_count += 2 * i * j;
            }
        }
    }
    
    // 计算长方形的个数
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            rectangle_count += (N - i + 1) * (M - j + 1);
        }
    }
    
    // 减去正方形的个数，得到长方形的个数
    rectangle_count -= square_count;
    
    printf("%lld %lld\n", square_count, rectangle_count);
    
    return 0;
}