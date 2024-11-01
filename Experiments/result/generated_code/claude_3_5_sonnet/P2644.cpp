#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_M 30
#define MAX_N 30
#define INF 0x3f3f3f3f

int P, M, N;
int pond[MAX_M][MAX_N];
int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
int start_x, start_y, end_x, end_y;

long long dp[MAX_M][MAX_N][MAX_M * MAX_N];
bool visited[MAX_M][MAX_N];

bool is_valid(int x, int y) {
    return x >= 0 && x < M && y >= 0 && y < N && pond[x][y] != 2;
}

void dfs(int x, int y, int energy, int platinum, long long *min_energy, long long *count, int *max_platinum, long long *platinum_count) {
    if (energy > P) return;
    if (x == end_x && y == end_y) {
        if (energy < *min_energy) {
            *min_energy = energy;
            *count = 1;
            *max_platinum = platinum;
            *platinum_count = 1;
        } else if (energy == *min_energy) {
            (*count)++;
            if (platinum > *max_platinum) {
                *max_platinum = platinum;
                *platinum_count = 1;
            } else if (platinum == *max_platinum) {
                (*platinum_count)++;
            }
        }
        return;
    }

    visited[x][y] = true;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (is_valid(nx, ny) && !visited[nx][ny]) {
            int new_energy = energy;
            int new_platinum = platinum;
            if (pond[nx][ny] == 0) {
                new_energy++;
            } else if (pond[nx][ny] == 5) {
                new_energy += 2;
                new_platinum++;
            }
            dfs(nx, ny, new_energy, new_platinum, min_energy, count, max_platinum, platinum_count);
        }
    }
    visited[x][y] = false;
}

int main() {
    scanf("%d %d %d", &P, &M, &N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &pond[i][j]);
            if (pond[i][j] == 3) {
                start_x = i;
                start_y = j;
            } else if (pond[i][j] == 4) {
                end_x = i;
                end_y = j;
            }
        }
    }

    long long min_energy = INF, count = 0;
    int max_platinum = 0;
    long long platinum_count = 0;

    dfs(start_x, start_y, 0, 0, &min_energy, &count, &max_platinum, &platinum_count);

    if (min_energy == INF) {
        printf("-1\n");
    } else {
        printf("%lld %lld\n", min_energy, count);
        if (max_platinum == 0) {
            printf("-1\n");
        } else {
            printf("%d %lld\n", max_platinum, platinum_count);
        }
    }

    return 0;
}