#include <stdio.h>
#include <string.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[1001][1001];
    int count = 0;

    // 读取矩形
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    // 遍历矩形寻找 "hehe"
    for (int i = 0; i < n - 3; i++) {
        for (int j = 0; j < m - 3; j++) {
            if (grid[i][j] == 'h' && grid[i][j + 1] == 'e' && grid[i][j + 2] == 'h' && grid[i][j + 3] == 'e') {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}