#include <stdio.h>

int main() {
    int k, m;
    scanf("%d", &k);
    
    // 确定最小的 m，使得在第一个好人被杀死前，k 个坏人先被杀死
    // 初始 m 为 2，因为至少需要两个数才能杀掉一个人
    m = 2;
    while (1) {
        int count_good = 0; // 好人被杀死的计数
        int count_bad = 0;  // 坏人被杀死的计数
        
        for (int i = 1; i <= 2 * k; i++) {
            if (i <= k) {
                // 好人
                if (count_good == k - 1) {
                    // 好人被杀死的次数达到 k-1 次，停止计数
                    break;
                }
                count_good++;
            } else {
                // 坏人
                if (count_bad == k) {
                    // 坏人被杀死的次数达到 k 次，输出 m 并停止程序
                    printf("%d\n", m);
                    return 0;
                }
                count_bad++;
            }
            m++;
        }
    }
    return 0;
}