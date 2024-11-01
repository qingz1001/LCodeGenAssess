#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_R 500
#define MAX_C 500

int R, C, A, B;
int grid[MAX_R][MAX_C];
int prefixSum[MAX_R][MAX_C];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int getSum(int x1, int y1, int x2, int y2) {
    int sum = prefixSum[x2][y2];
    if (x1 > 0) sum -= prefixSum[x1-1][y2];
    if (y1 > 0) sum -= prefixSum[x2][y1-1];
    if (x1 > 0 && y1 > 0) sum += prefixSum[x1-1][y1-1];
    return sum;
}

int check(int minChips) {
    int cuts[MAX_R+1][MAX_C+1];
    for (int i = 0; i <= R; i++)
        for (int j = 0; j <= C; j++)
            cuts[i][j] = 0;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (getSum(i, j, i, j) >= minChips) {
                cuts[i+1][j+1] = 1;
            }
        }
    }

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cuts[i][j] += cuts[i-1][j] + cuts[i][j-1] - cuts[i-1][j-1];
        }
    }

    for (int i = 0; i <= R-A; i++) {
        for (int j = 0; j <= C-B; j++) {
            if (cuts[i+A][j+B] - cuts[i][j+B] - cuts[i+A][j] + cuts[i][j] == A*B) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    scanf("%d %d %d %d", &R, &C, &A, &B);

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Calculate prefix sum
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            prefixSum[i][j] = grid[i][j];
            if (i > 0) prefixSum[i][j] += prefixSum[i-1][j];
            if (j > 0) prefixSum[i][j] += prefixSum[i][j-1];
            if (i > 0 && j > 0) prefixSum[i][j] -= prefixSum[i-1][j-1];
        }
    }

    int low = 0, high = 4000 * MAX_R * MAX_C;
    int result = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (check(mid)) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("%d\n", result);

    return 0;
}