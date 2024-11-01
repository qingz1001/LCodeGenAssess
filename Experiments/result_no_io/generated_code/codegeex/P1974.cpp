#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    // 初始情况下，每个基因组只有一对基元
    long long total_pairs = n;

    // 每次聚合都会产生一个额外的基元对
    // 并且每个基因组中的每对基元都会与另一个基因组中的每对基元两两聚合产生一个新的基元对
    // 因此每次聚合产生的基元对数为 (total_pairs / 2) * (total_pairs / 2) + 1
    // 其中 total_pairs / 2 表示当前基因组数量的一半
    // (total_pairs / 2) * (total_pairs / 2) 表示每对基因组之间的聚合产生的基元对数
    // +1 表示每次聚合产生的额外基元对
    for (int i = 0; i < n - 1; i++) {
        total_pairs += (total_pairs / 2) * (total_pairs / 2) + 1;
    }

    printf("%lld\n", total_pairs);
    return 0;
}