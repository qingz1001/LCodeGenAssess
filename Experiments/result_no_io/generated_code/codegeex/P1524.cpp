#include <stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    char grid[2][201][201];

    // 读取正面图案
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[0][i]);
    }

    // 读取反面图案
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[1][i]);
    }

    int minStitches = 0;

    // 遍历网格，计算最少针数
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[0][i][j] == 'X' || grid[1][i][j] == 'X') {
                // 如果交叉点，两针
                minStitches += 2;
            } else if (grid[0][i][j] == '/' || grid[1][i][j] == '/') {
                // 如果从右上角到左下角的线，一针
                minStitches++;
            } else if (grid[0][i][j] == '\\' || grid[1][i][j] == '\\') {
                // 如果从左上角到右下角的线，一针
                minStitches++;
            }
        }
    }

    printf("%d\n", minStitches);
    return 0;
}