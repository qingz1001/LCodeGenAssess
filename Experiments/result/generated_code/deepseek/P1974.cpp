#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    // 计算最终基因组的总能量
    int total_energy = n - 1;
    
    printf("%d\n", total_energy);
    
    return 0;
}