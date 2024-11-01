#include <stdio.h>
#include <string.h>

#define MAXN 900

int n, ans[MAXN][MAXN];
char a[MAXN][MAXN];

int main() {
    scanf("%d", &n);
    
    // 读取输入
    for (int i = 0; i < 2 * n; i++) {
        scanf("%s", a[i]);
    }
    
    // 初始化
    memset(ans, 0, sizeof(ans));
    
    // 遍历大菱形网格
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            if (a[i][j] == '!') {
                // 判断上方是否有边
                if (i > 0 && j > 0 && a[i-1][j-1] == '!') {
                    ans[i][j] |= 1;
                }
                // 判断下方是否有边
                if (i < 2 * n - 1 && j < 2 * n - 1 && a[i+1][j+1] == '!') {
                    ans[i][j] |= 2;
                }
                // 判断左方是否有边
                if (i > 0 && j < 2 * n - 1 && a[i-1][j+1] == '!') {
                    ans[i][j] |= 4;
                }
                // 判断右方是否有边
                if (i < 2 * n - 1 && j > 0 && a[i+1][j-1] == '!') {
                    ans[i][j] |= 8;
                }
            }
        }
    }
    
    // 输出结果
    printf("%d\n", n);
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            if ((i + j) % 2 == 0) {
                printf("%d", ans[i][j] > 0);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    
    return 0;
}