#include <stdio.h>
#include <stdlib.h>

#define MAXN 500
#define MAXELEVATION 1000000

int N;
int elevation[MAXN][MAXN];
int visited[MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int dfs(int x, int y, int target, int count) {
    if (x < 0 || x >= N || y < 0 || y >= N || visited[x][y]) {
        return 0;
    }
    if (count >= target) {
        return 1;
    }
    visited[x][y] = 1;
    int result = 0;
    result += dfs(x + 1, y, target, count + 1);
    result += dfs(x - 1, y, target, count + 1);
    result += dfs(x, y + 1, target, count + 1);
    result += dfs(x, y - 1, target, count + 1);
    visited[x][y] = 0;
    return result;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &elevation[i][j]);
        }
    }

    int maxDiff = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < N; l++) {
                    maxDiff = max(maxDiff, abs(elevation[i][j] - elevation[k][l]));
                }
            }
        }
    }

    int target = (N * N + 1) / 2;
    int low = 0, high = maxDiff;
    while (low < high) {
        int mid = (low + high) / 2;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                visited[i][j] = 0;
            }
        }
        if (dfs(i, j, mid, 0)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    printf("%d\n", low);

    return 0;
}