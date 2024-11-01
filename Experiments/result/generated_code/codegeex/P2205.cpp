#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100005

int n, k;
int a[MAX], b[MAX];
int sum[MAX];

int main() {
    char ch;
    int i, j, l, r, ans = 0;
    
    // 读取输入的n和k
    scanf("%d%d", &n, &k);
    
    // 初始化数组a和b
    a[0] = 0;
    b[0] = 0;
    
    // 读取每次移动的值和方向
    for (i = 1; i <= n; i++) {
        scanf("%d %c", &a[i], &ch);
        if (ch == 'R') {
            b[i] = b[i - 1] + a[i];
        } else {
            b[i] = b[i - 1] - a[i];
        }
    }
    
    // 对数组b进行排序
    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            if (b[i] > b[j]) {
                int tmp = b[i];
                b[i] = b[j];
                b[j] = tmp;
            }
        }
    }
    
    // 计算前缀和数组sum
    sum[0] = 0;
    for (i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }
    
    // 计算被至少涂上K层涂料的栅栏数
    for (i = 1; i <= n; i++) {
        l = 0;
        r = i - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (b[mid] < b[i] - k) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (l <= n && b[l] < b[i] - k) {
            l++;
        }
        ans += sum[i - 1] - sum[l - 1];
    }
    
    // 输出结果
    printf("%d\n", ans);
    
    return 0;
}