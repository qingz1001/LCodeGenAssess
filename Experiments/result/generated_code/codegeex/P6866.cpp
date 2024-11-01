#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char matrix[100][100];
    int count = 0;

    // 读取矩阵
    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }

    // 遍历矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == '*') {
                // 检查上方是否有'*'
                int k = i - 1;
                while (k >= 0 && matrix[k][j] == '.') {
                    k--;
                }
                // 检查左方是否有'*'
                int l = j - 1;
                while (l >= 0 && matrix[i][l] == '.') {
                    l--;
                }
                // 检查右方是否有'*'
                int r = j + 1;
                while (r < m && matrix[i][r] == '.') {
                    r++;
                }
                // 检查下方是否有'*'
                int s = i + 1;
                while (s < n && matrix[s][j] == '.') {
                    s++;
                }
                // 检查右下角是否有'*'
                int t = s;
                int u = r;
                while (t < n && u < m && matrix[t][u] == '.') {
                    t++;
                    u++;
                }
                // 检查左下角是否有'*'
                t = s;
                u = l;
                while (t < n && u >= 0 && matrix[t][u] == '.') {
                    t++;
                    u--;
                }
                // 检查右上角是否有'*'
                t = i;
                u = r;
                while (t >= 0 && u < m && matrix[t][u] == '.') {
                    t--;
                    u++;
                }
                // 检查左上角是否有'*'
                t = i;
                u = l;
                while (t >= 0 && u >= 0 && matrix[t][u] == '.') {
                    t--;
                    u--;
                }
                // 如果四个角都有'*'，则这是一个新的长方形
                if (matrix[i][l] == '*' && matrix[i][r] == '*' && matrix[s][j] == '*' && matrix[t][u] == '*') {
                    count++;
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}