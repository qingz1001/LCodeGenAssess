#include <stdio.h>
#include <stdbool.h>

#define MAX_N 100
#define MAX_M 100

bool canTransform(int n, int m, int board1[MAX_N][MAX_M], int board2[MAX_N][MAX_M]) {
    int row_parity1[MAX_N] = {0};
    int row_parity2[MAX_N] = {0};
    int col_count1[MAX_M] = {0};
    int col_count2[MAX_M] = {0};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            row_parity1[i] ^= board1[i][j];
            row_parity2[i] ^= board2[i][j];
            col_count1[j] += board1[i][j];
            col_count2[j] += board2[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        if (row_parity1[i] != row_parity2[i]) {
            return false;
        }
    }

    for (int j = 0; j < m; j++) {
        if (col_count1[j] != col_count2[j]) {
            return false;
        }
    }

    return true;
}

int main() {
    int k;
    scanf("%d", &k);

    while (k--) {
        int n, m;
        scanf("%d %d", &n, &m);

        int board1[MAX_N][MAX_M];
        int board2[MAX_N][MAX_M];

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