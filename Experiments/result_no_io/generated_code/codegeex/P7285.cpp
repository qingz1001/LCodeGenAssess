#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, x = 0, y = 0;
        scanf("%d", &n);
        int a[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        
        // 贪心策略：将第一个0变成1，这样可以将整个数组变成全1
        if (n > 0 && a[0] == 0) {
            a[0] = 1;
            y++;
        }
        
        // 计算最长连续1的子段长度
        int maxLen = 0, currentLen = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                currentLen++;
            } else {
                if (currentLen > maxLen) {
                    maxLen = currentLen;
                }
                currentLen = 0;
            }
        }
        if (currentLen > maxLen) {
            maxLen = currentLen;
        }
        
        // 输出结果
        printf("%d\n", maxLen - y);
        for (int i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }
    return 0;
}