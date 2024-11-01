#include <stdio.h>
#include <string.h>

#define MAXN 205
#define MAXP 11

int N, M, P;
int sum[MAXN][MAXN];
int matrix[MAXN][MAXN];

void solve() {
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            int s = sum[i][j];
            for (int x = 0; x < P; x++) {
                if (s >= matrix[i-1][j-1] + matrix[i-1][j] + matrix[i][j-1] + x &&
                    s < matrix[i-1][j-1] + matrix[i-1][j] + matrix[i][j-1] + x + P) {
                    matrix[i][j] = x;
                    break;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &M, &P);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &sum[i][j]);
        }
    }

    memset(matrix, 0, sizeof(matrix));
    solve();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d", matrix[i][j]);
            if (j < M - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}