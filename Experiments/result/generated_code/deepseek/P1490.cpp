#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    // 计算最少需要的数目
    int min_count = ceil(log2(n + 1));

    // 计算最少个数的组成方案个数
    int count_ways = pow(2, min_count - 1);

    printf("%d %d\n", min_count, count_ways);

    return 0;
}