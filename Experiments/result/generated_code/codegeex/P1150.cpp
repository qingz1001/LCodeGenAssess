#include <stdio.h>

int main() {
    long long n, k, totalCigarettes, totalButts;
    
    // 读取输入的n和k
    scanf("%lld %lld", &n, &k);
    
    totalCigarettes = n; // 初始时Peter有n根烟
    totalButts = n;      // 初始时Peter有n个烟蒂
    
    // 当烟蒂数量足够换新的烟时，进行循环
    while (totalButts >= k) {
        // 计算可以换的新烟的数量
        long long newCigarettes = totalButts / k;
        
        // 更新总烟数量
        totalCigarettes += newCigarettes;
        
        // 更新烟蒂数量
        totalButts = newCigarettes + (totalButts % k);
    }
    
    // 输出最终Peter能抽到的烟的数量
    printf("%lld\n", totalCigarettes);
    
    return 0;
}