#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_M 30
#define MAX_N 29
#define MAX_K 5
#define MAX_STATES (1 << MAX_K)

typedef struct {
    int x, y;
} Point;

int m, n, k, H;
char maze[MAX_M][MAX_N];
int p[MAX_STATES];
double dp[MAX_M][MAX_N][MAX_K + 1][MAX_STATES];
int visited[MAX_M][MAX_N][MAX_K + 1][MAX_STATES];
Point start;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

double dfs(int x, int y, int health, int state) {
    if (health <= 0) return 0.0;
    if (maze[x][y] == '@') return 1.0;
    if (visited[x][y][health][state]) return dp[x][y][health][state];

    visited[x][y][health][state] = 1;
    double max_prob = 0.0;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || nx >= m || ny < 0 || ny >= n || maze[nx][ny] == '#') continue;

        if (maze[nx][ny] >= 'A' && maze[nx][ny] <= 'A' + k - 1) {
            int trap_index = maze[nx][ny] - 'A';
            int trap_bit = 1 << trap_index;
            int new_state = state | trap_bit;

            double prob_harmful = (double)p[new_state] / (double)p[state];
            double prob_safe = 1.0 - prob_harmful;

            double prob_alive = prob_safe * dfs(nx, ny, health, new_state) +
                                prob_harmful * dfs(nx, ny, health - 1, new_state);

            if (prob_alive > max_prob) max_prob = prob_alive;
        } else {
            double prob_alive = dfs(nx, ny, health, state);
            if (prob_alive > max_prob) max_prob = prob_alive;
        }
    }

    dp[x][y][health][state] = max_prob;
    return max_prob;
}

int main() {
    scanf("%d %d %d %d", &m, &n, &k, &H);
    for (int i = 0; i < m; i++) {
        scanf("%s", maze[i]);
        for (int j = 0; j < n; j++) {
            if (maze[i][j] == '$') {
                start.x = i;
                start.y = j;
            }
        }
    }
    for (int i = 0; i < (1 << k); i++) {
        scanf("%d", &p[i]);
    }

    double result = dfs(start.x, start.y, H, 0);
    printf("%.3f\n", result);

    return 0;
}