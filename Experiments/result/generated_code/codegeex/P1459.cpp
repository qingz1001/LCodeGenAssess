#include <stdio.h>

int main() {
    int n, a[1001], one = 0, two = 0, three = 0, ans = 0;
    
    // 读取奖牌个数
    scanf("%d", &n);
    
    // 读取每个奖牌的值并统计1、2、3的数量
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (a[i] == 1) one++;
        else if (a[i] == 2) two++;
        else three++;
    }
    
    // 按照升序的要求重新排列奖牌
    for (int i = 1; i <= n; i++) {
        if (i <= one) {
            while (a[i] != 1) {
                ans++;
                // 找到当前位置后面最近的1，并交换
                for (int j = i + 1; j <= n; j++) {
                    if (a[j] == 1) {
                        a[i] = 1;
                        a[j] = a[i + 1];
                        break;
                    }
                }
            }
        } else if (i <= one + two) {
            while (a[i] != 2) {
                ans++;
                // 找到当前位置后面最近的2，并交换
                for (int j = i + 1; j <= n; j++) {
                    if (a[j] == 2) {
                        a[i] = 2;
                        a[j] = a[i + 1];
                        break;
                    }
                }
            }
        } else {
            while (a[i] != 3) {
                ans++;
                // 找到当前位置后面最近的3，并交换
                for (int j = i + 1; j <= n; j++) {
                    if (a[j] == 3) {
                        a[i] = 3;
                        a[j] = a[i + 1];
                        break;
                    }
                }
            }
        }
    }
    
    // 输出最少交换次数
    printf("%d\n", ans);
    
    return 0;
}