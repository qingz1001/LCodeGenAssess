#include <stdio.h>
#include <stdlib.h>

#define N 3
#define M 9

int clocks[N][N];
int moves[M][N];

void applyMove(int move) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (moves[move - 1][i * N + j]) {
                clocks[i][j] = (clocks[i][j] % 12) + 1;
            }
        }
    }
}

int isAllTwelve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (clocks[i][j] != 12) return 0;
        }
    }
    return 1;
}

void dfs(int depth, int path[], int *minDepth, int *bestPath) {
    if (isAllTwelve()) {
        if (depth < *minDepth || (depth == *minDepth && path[0] < bestPath[0])) {
            *minDepth = depth;
            for (int i = 0; i < depth; i++) {
                bestPath[i] = path[i];
            }
        }
        return;
    }
    if (depth >= *minDepth) return;

    for (int move = 1; move <= M; move++) {
        path[depth] = move;
        applyMove(move);
        dfs(depth + 1, path, minDepth, bestPath);
        applyMove(move); // Backtrack
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &clocks[i][j]);
        }
    }

    for (int move = 0; move < M; move++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                moves[move][i * N + j] = (move + 1) / (i * N + j + 1) % 2;
            }
        }
    }

    int minDepth = M;
    int bestPath[M];
    int path[M];

    dfs(0, path, &minDepth, bestPath);

    for (int i = 0; i < minDepth; i++) {
        printf("%d ", bestPath[i]);
    }
    printf("\n");

    return 0;
}