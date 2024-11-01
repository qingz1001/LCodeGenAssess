#include <stdio.h>

#define MAX_N 100

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int lights[MAX_N][MAX_N] = {0};

    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        // Light the area around the torch
        for (int dx = -2; dx <= 2; ++dx) {
            for (int dy = -2; dy <= 2; ++dy) {
                if (x + dx >= 1 && x + dx <= n && y + dy >= 1 && y + dy <= n) {
                    lights[x + dx - 1][y + dy - 1] = 1;
                }
            }
        }
    }

    for (int i = 0; i < k; ++i) {
        int o, p;
        scanf("%d %d", &o, &p);
        // Light the entire cell where the obsidian is
        lights[o - 1][p - 1] = 1;
    }

    int monsters = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (lights[i][j] == 0) {
                monsters++;
            }
        }
    }

    printf("%d\n", monsters);

    return 0;
}