#include <stdio.h>
#include <stdlib.h>

#define MAXN 101

int N, M;
int bad[MAXN][MAXN];

int is_valid(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || (x1 == x2 && y1 > y2)) return 0;
    for (int i = x1; i <= x2; ++i) {
        for (int j = y1; j <= y2; ++j) {
            if (bad[i][j]) return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        bad[x][y] = 1;
    }

    int max_area = 0;
    for (int x1 = 1; x1 + x1 <= N; ++x1) {
        for (int y1 = 1; y1 + y1 - 1 <= 2 * N - 1; ++y1) {
            for (int x2 = x1 + 1; x2 + x2 <= N; ++x2) {
                for (int y2 = y1 + y1 - 1; y2 + y2 - 1 <= 2 * N - 1; ++y2) {
                    if (is_valid(x1, y1, x2, y2) && is_valid(x2, y2, N, 2 * N - 1)) {
                        int area1 = (x2 - x1 + 1) * (x2 - x1 + 2) / 2;
                        int area2 = (N - x2 + 1) * (N - x2 + 2) / 2;
                        if (area1 + area2 > max_area) {
                            max_area = area1 + area2;
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", max_area);
    return 0;
}