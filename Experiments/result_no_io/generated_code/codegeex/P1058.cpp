#include <stdio.h>
#include <string.h>

#define MAXN 50
#define MAXM 50
#define MAXH 10000

int main() {
    int m, n, h;
    int grid[MAXN + 1][MAXN + 1];
    char pic[MAXH + 1][4 * MAXN + 3 * MAXN + 2];

    // 初始化图片矩阵
    memset(pic, '.', sizeof(pic));

    // 输入矩阵的大小
    scanf("%d %d", &m, &n);

    // 输入每个格子上的积木数
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &grid[i][j]);
            h = grid[i][j];
            // 计算图片的高度
            if (h > h) {
                h = h;
            }
        }
    }

    // 构建立体图
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int h = grid[i][j];
            for (int k = 0; k < h; k++) {
                // 计算每个积木的左下角坐标
                int x = (i - 1) * 4 + k * 2;
                int y = (j - 1) * 3 + k * 2;

                // 绘制积木
                pic[x][y] = '+';
                pic[x][y + 1] = '-';
                pic[x][y + 2] = '-';
                pic[x][y + 3] = '-';
                pic[x][y + 4] = '+';
                pic[x + 1][y] = '|';
                pic[x + 1][y + 1] = ' ';
                pic[x + 1][y + 2] = ' ';
                pic[x + 1][y + 3] = ' ';
                pic[x + 1][y + 4] = '|';
                pic[x + 1][y + 5] = '/';
                pic[x + 2][y] = '+';
                pic[x + 2][y + 1] = '-';
                pic[x + 2][y + 2] = '-';
                pic[x + 2][y + 3] = '-';
                pic[x + 2][y + 4] = '+';
                pic[x + 2][y + 5] = ' ';
                pic[x + 3][y] = '|';
                pic[x + 3][y + 1] = ' ';
                pic[x + 3][y + 2] = ' ';
                pic[x + 3][y + 3] = ' ';
                pic[x + 3][y + 4] = '|';
                pic[x + 3][y + 5] = '/';
                pic[x + 4][y] = '+';
                pic[x + 4][y + 1] = '-';
                pic[x + 4][y + 2] = '-';
                pic[x + 4][y + 3] = '-';
                pic[x + 4][y + 4] = '+';
            }
        }
    }

    // 输出图片矩阵
    int K = 0, L = 0;
    for (int i = 0; i < MAXH; i++) {
        for (int j = 0; j < 4 * n + 3 * n + 2; j++) {
            if (pic[i][j] != '.') {
                K = i + 1;
                L = j + 1;
                break;
            }
        }
    }

    for (int i = K - 1; i >= 0; i--) {
        for (int j = 0; j < L; j++) {
            printf("%c", pic[i][j]);
        }
        printf("\n");
    }

    return 0;
}