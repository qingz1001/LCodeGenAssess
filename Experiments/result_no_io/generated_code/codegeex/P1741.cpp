#include <stdio.h>
#include <string.h>

#define MAXN 888

int n, ans;
char grid[MAXN][MAXN * 2];

int main() {
    scanf("%d", &n);
    
    // 读取输入的网格
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i + n]);
    }
    
    // 遍历网格中的每个点
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n * 2; j++) {
            // 检查当前点是否存在边
            if (grid[i][j] == ' ') {
                continue;
            }
            
            // 检查四个方向上的点是否存在边
            // 向右上方
            for (int k = 1; i - k >= 0 && j + k < n * 2; k++) {
                if (grid[i - k][j + k] == ' ') {
                    break;
                }
                if (grid[i - k][j + k] == '!' && grid[i][j + k] == '!' && grid[i - k][j] == '!') {
                    ans++;
                }
            }
            
            // 向右下方
            for (int k = 1; i + k < n * 2 && j + k < n * 2; k++) {
                if (grid[i + k][j + k] == ' ') {
                    break;
                }
                if (grid[i + k][j + k] == '!' && grid[i][j + k] == '!' && grid[i + k][j] == '!') {
                    ans++;
                }
            }
            
            // 向左上方
            for (int k = 1; i - k >= 0 && j - k >= 0; k++) {
                if (grid[i - k][j - k] == ' ') {
                    break;
                }
                if (grid[i - k][j - k] == '!' && grid[i][j - k] == '!' && grid[i - k][j] == '!') {
                    ans++;
                }
            }
            
            // 向左下方
            for (int k = 1; i + k < n * 2 && j - k >= 0; k++) {
                if (grid[i + k][j - k] == ' ') {
                    break;
                }
                if (grid[i + k][j - k] == '!' && grid[i][j - k] == '!' && grid[i + k][j] == '!') {
                    ans++;
                }
            }
        }
    }
    
    printf("%d\n", ans);
    return 0;
}