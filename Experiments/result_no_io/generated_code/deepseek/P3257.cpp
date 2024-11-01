#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 10000
#define MAX_M 20

int n, m, cost1, cost2;
int map[MAX_M][MAX_N];
int dp[MAX_N][MAX_M][6][6]; // dp[x][y][jump][combo]

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &cost1, &cost2);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &map[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k <= 5; k++) {
                for (int l = 0; l <= 5; l++) {
                    dp[i][j][k][l] = INT_MIN;
                }
            }
        }
    }

    dp[0][0][1][1] = map[0][0];

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            for (int jump = 1; jump <= 5; jump++) {
                for (int combo = 1; combo <= 5; combo++) {
                    if (dp[x][y][jump][combo] == INT_MIN) continue;

                    // Move right
                    if (x + 1 < n && map[y][x + 1] != -1) {
                        dp[x + 1][y][jump][combo] = max(dp[x + 1][y][jump][combo], dp[x][y][jump][combo] + map[y][x + 1]);
                    }

                    // Jump up
                    if (y + jump < m && map[y + jump][x + 1] != -1) {
                        dp[x + 1][y + jump][jump][combo] = max(dp[x + 1][y + jump][jump][combo], dp[x][y][jump][combo] + map[y + jump][x + 1]);
                    }

                    // Combo jump
                    if (combo > 1 && y - jump >= 0 && map[y - jump][x + 1] != -1) {
                        dp[x + 1][y - jump][jump][combo - 1] = max(dp[x + 1][y - jump][jump][combo - 1], dp[x][y][jump][combo] + map[y - jump][x + 1]);
                    }
                }
            }
        }
    }

    int max_score = INT_MIN;
    int min_combo = 6;
    int min_jump = 6;

    for (int jump = 1; jump <= 5; jump++) {
        for (int combo = 1; combo <= 5; combo++) {
            if (dp[n - 1][m - 1][jump][combo] > max_score) {
                max_score = dp[n - 1][m - 1][jump][combo];
                min_combo = combo;
                min_jump = jump;
            } else if (dp[n - 1][m - 1][jump][combo] == max_score) {
                if (combo < min_combo) {
                    min_combo = combo;
                    min_jump = jump;
                } else if (combo == min_combo && jump < min_jump) {
                    min_jump = jump;
                }
            }
        }
    }

    if (max_score == INT_MIN) {
        printf("mission failed\n");
    } else {
        printf("%d %d %d\n", max_score, min_combo, min_jump);
    }

    return 0;
}