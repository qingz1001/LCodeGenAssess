#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 182
#define MAX_M 182

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int screen[MAX_N][MAX_M];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            scanf(" %d", &screen[i][j]);
        }
    }

    int result[MAX_N][MAX_M];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (screen[i][j] == 1) {
                result[i][j] = 0;
            } else {
                result[i][j] = INT_MAX;
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (screen[i][j] == 1) continue;

            if (i > 0) result[i][j] = fmin(result[i][j], result[i - 1][j] + 1);
            if (j > 0) result[i][j] = fmin(result[i][j], result[i][j - 1] + 1);
        }
    }

    for (int i = N - 1; i >= 0; --i) {
        for (int j = M - 1; j >= 0; --j) {
            if (screen[i][j] == 1) continue;

            if (i < N - 1) result[i][j] = fmin(result[i][j], result[i + 1][j] + 1);
            if (j < M - 1) result[i][j] = fmin(result[i][j], result[i][j + 1] + 1);
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%d", result[i][j]);
            if (j < M - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}