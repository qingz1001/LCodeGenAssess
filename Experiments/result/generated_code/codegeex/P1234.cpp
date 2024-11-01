#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char rect[n][m];
    int count = 0;

    // 读取矩形
    for (int i = 0; i < n; i++) {
        scanf("%s", rect[i]);
    }

    // 查找 "hehe"
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 3; j++) {
            if (rect[i][j] == 'h' && rect[i][j+1] == 'e' && rect[i][j+2] == 'h' && rect[i][j+3] == 'e') {
                count++;
            }
        }
    }

    // 输出结果
    printf("%d\n", count);

    return 0;
}