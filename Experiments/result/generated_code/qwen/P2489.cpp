#include <stdio.h>
#include <stdlib.h>

#define MAXM 31
#define MAXN 30
#define MAXK 6

typedef struct {
    int x, y;
} Point;

double dp[MAXM][MAXN][MAXK][2];
int p[1 << MAXK];

int main() {
    int m, n, k, H;
    scanf("%d %d %d %d", &m, &n, &k, &H);
    char grid[MAXM][MAXN];
    for (int i = 0; i < m; i++) {
        scanf("%s", grid[i]);
    }
    for (int i = 0; i < 1 << k; i++) {
        scanf("%d", &p[i]);
    }

    double sum_p = 0;
    for (int i = 0; i < 1 << k; i++) {
        sum_p += p[i];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < k; l++) {
                dp[i][j][l][0] = -1;
                dp[i][j][l][1] = -1;
            }
        }
    }

    Point start;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '$') {
                start.x = i;
                start.y = j;
                break;
            }
        }
    }

    dp[start.x][start.y][0][1] = 1.0;

    for (int step = 1; step <= m * n; step++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int l = 0; l < k; l++) {
                    if (dp[i][j][l][1] == -1) continue;

                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            if (dx == 0 && dy == 0) continue;
                            if (abs(dx) + abs(dy) != 1) continue;

                            int ni = i + dx, nj = j + dy;
                            if (ni < 0 || ni >= m || nj < 0 || nj >= n) continue;

                            if (grid[ni][nj] == '#') continue;

                            int trap_state = 0;
                            for (int tl = 0; tl < k; tl++) {
                                if (grid[ni][nj] == 'A' + tl) {
                                    trap_state |= (1 << tl);
                                }
                            }

                            int no_damage = 1, has_damage = 0;
                            if ((trap_state >> l) & 1) {
                                has_damage = 1;
                            } else {
                                no_damage = 1;
                            }

                            if (no_damage) {
                                dp[ni][nj][l][1] = max(dp[ni][nj][l][1], dp[i][j][l][1]);
                            } else {
                                dp[ni][nj][l][0] = max(dp[ni][nj][l][0], dp[i][j][l][1] * (double)p[trap_state] / sum_p);
                            }
                        }
                    }
                }
            }
        }
    }

    double ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < k; l++) {
                ans += dp[i][j][l][1];
            }
        }
    }

    printf("%.3f\n", ans);

    return 0;
}

double max(double a, double b) {
    return a > b ? a : b;
}