#include <stdio.h>
#include <string.h>

#define MAX_N 101
#define MAX_M 10001

int N, M;
int damaged[MAX_N][2 * MAX_N];
int dp[MAX_N][MAX_N][MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int is_valid(int x, int y, int size) {
    if (x + size - 1 > N || y + size - 1 > 2 * N - 1) return 0;
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + i - x + 1; j++) {
            if (damaged[i][j]) return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d", &N);
    scanf("%d", &M);

    memset(damaged, 0, sizeof(damaged));
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        damaged[x][y] = 1;
    }

    memset(dp, -1, sizeof(dp));

    for (int size = 1; size <= N; size++) {
        for (int x = 1; x <= N - size + 1; x++) {
            for (int y = 1; y <= 2 * N - size; y++) {
                if (is_valid(x, y, size)) {
                    dp[x][y][size] = size * size;
                    for (int s = 1; s < size; s++) {
                        for (int xx = x; xx <= x + size - s; xx++) {
                            for (int yy = y; yy <= y + size - s; yy++) {
                                if (dp[x][y][s] != -1 && dp[xx][yy][size-s] != -1) {
                                    dp[x][y][size] = max(dp[x][y][size], dp[x][y][s] + dp[xx][yy][size-s]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int result = 0;
    for (int x1 = 1; x1 <= N; x1++) {
        for (int y1 = 1; y1 <= 2 * N - 1; y1++) {
            for (int s1 = 1; s1 <= N; s1++) {
                if (dp[x1][y1][s1] == -1) continue;
                for (int x2 = 1; x2 <= N; x2++) {
                    for (int y2 = 1; y2 <= 2 * N - 1; y2++) {
                        for (int s2 = 1; s2 <= N; s2++) {
                            if (dp[x2][y2][s2] == -1) continue;
                            result = max(result, dp[x1][y1][s1] + dp[x2][y2][s2]);
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", result);
    return 0;
}