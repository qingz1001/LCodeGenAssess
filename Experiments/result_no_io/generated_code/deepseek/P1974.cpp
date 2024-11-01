#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    // 计算最终基因组的总能量
    // 每次聚合产生一个额外的基元对，总共需要进行 n-1 次聚合
    // 每次聚合后，基因组的数量减少1，直到只剩下一个基因组
    // 每次聚合的总能量为当前基因组数量减1
    int total_energy = (n - 1) * n / 2; // 计算所有基因组两两聚合产生的能量
    total_energy += (n - 1); // 加上每次聚合产生的额外基元对能量
    
    printf("%d\n", total_energy);
    
    return 0;
}