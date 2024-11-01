#include <stdio.h>
#include <math.h>

#define MAXN 55
#define MAXM 3162

int n, m, ans;
int a[MAXN + 5][MAXM + 5], b[MAXM + 5], c[MAXM + 5], d[MAXM + 5];

int main() {
    // 读取柱子数
    scanf("%d", &n);
    
    // 初始化
    m = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= MAXM; j++) {
            a[i][j] = -1;
        }
    }
    
    // 逐个球放入柱子
    for (int i = 1; i <= MAXM; i++) {
        if (a[1][i] == -1) {
            // 放入第一个柱子
            a[1][i] = i;
            b[i] = 1;
            m = 1;
            ans = i;
            
            // 尝试放入更多球
            for (int j = i + 1; j <= MAXM; j++) {
                int k = sqrt(j - i);
                k *= k;
                if (k != j - i) continue;
                int t = b[i];
                for (int l = 1; l <= t; l++) {
                    if (a[l][j] == -1 && a[l][i] != -1) {
                        a[l][j] = j;
                        b[j] = l;
                        m++;
                        ans = j;
                        break;
                    }
                }
            }
            
            // 清除已放置的球
            for (int j = 1; j <= m; j++) {
                a[j][i] = -1;
                b[i] = 0;
            }
        }
    }
    
    // 输出结果
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= MAXM; j++) {
            if (a[i][j] != -1) {
                printf("%d ", a[i][j]);
            }
        }
        printf("\n");
    }
    
    return 0;
}