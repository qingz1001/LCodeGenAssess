#include <stdio.h>
#include <stdbool.h>

#define MAX 100

bool canTransform(int n, int m, int board1[MAX][MAX], int board2[MAX][MAX]) {
    int rowSum1[MAX] = {0};
    int rowSum2[MAX] = {0};
    int colSum1[MAX] = {0};
    int colSum2[MAX] = {0};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rowSum1[i] += board1[i][j];
            rowSum2[i] += board2[i][j];
            colSum1[j] += board1[i][j];
            colSum2[j] += board2[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        if (rowSum1[i] % 2 != rowSum2[i] % 2) {
            return false;
        }
    }

    for (int j = 0; j < m; j++) {
        if (colSum1[j] != colSum2[j]) {
            return false;
        }
    }

    return true;
}

int main() {
    int k, n, m;
    int board1[MAX][MAX], board2[MAX][MAX];

    scanf("%d", &k);
    while (k--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &board1[i][j]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &board2[i][j]);
            }
        }

        if (canTransform(n, m, board1, board2)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}