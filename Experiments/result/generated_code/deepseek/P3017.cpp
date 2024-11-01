#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_R 500
#define MAX_C 500

int R, C, A, B;
int grid[MAX_R][MAX_C];
int prefixSum[MAX_R + 1][MAX_C + 1];

void calculatePrefixSum() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            prefixSum[i][j] = grid[i - 1][j - 1] + prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
        }
    }
}

int getSum(int x1, int y1, int x2, int y2) {
    return prefixSum[x2][y2] - prefixSum[x1 - 1][y2] - prefixSum[x2][y1 - 1] + prefixSum[x1 - 1][y1 - 1];
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int check(int x) {
    int rowCuts[MAX_R + 1] = {0};
    int colCuts[MAX_C + 1] = {0};
    int rowCount = 0, colCount = 0;

    for (int i = 1; i <= R; i++) {
        int currentRowSum = 0;
        for (int j = 1; j <= C; j++) {
            if (getSum(rowCuts[rowCount] + 1, colCuts[colCount] + 1, i, j) >= x) {
                if (colCount < B - 1) {
                    colCuts[++colCount] = j;
                } else {
                    rowCuts[++rowCount] = i;
                    colCount = 0;
                    break;
                }
            }
        }
    }

    return rowCount >= A;
}

int main() {
    scanf("%d %d %d %d", &R, &C, &A, &B);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    calculatePrefixSum();

    int left = 0, right = prefixSum[R][C], result = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", result);
    return 0;
}