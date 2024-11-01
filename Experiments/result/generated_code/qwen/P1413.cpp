#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    // 使用数组记录每一行僵尸的数量
    int zombies[7] = {0};
    
    for (int i = 0; i < n; i++) {
        int p, t;
        scanf("%d %d", &p, &t);
        zombies[p]++;
    }
    
    // 计算最少需要的坚果数
    int min_peanuts = 0;
    for (int i = 1; i <= 6; i++) {
        if (zombies[i] > 0) {
            min_peanuts++;
        }
    }
    
    printf("%d\n", min_peanuts);
    
    return 0;
}