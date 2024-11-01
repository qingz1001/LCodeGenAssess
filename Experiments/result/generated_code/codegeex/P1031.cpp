#include <stdio.h>

int main() {
    int n, a[101], sum = 0, avg, ans = 0;
    
    // 读取输入
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    
    // 计算平均数
    avg = sum / n;
    
    // 计算移动次数
    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            a[i] -= avg;
            a[i + 1] += avg;
        } else if (i == n) {
            a[i] -= avg;
            a[i - 1] += avg;
        } else {
            a[i] -= avg;
            a[i + 1] += avg;
            ans += abs(a[i]);
        }
    }
    
    // 输出结果
    printf("%d\n", ans);
    
    return 0;
}