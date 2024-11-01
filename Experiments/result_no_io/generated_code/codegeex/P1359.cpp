#include <stdio.h>
#include <limits.h>

#define MAX_N 201

int n;
int r[MAX_N][MAX_N];

int min_cost(int start, int end) {
    if (start == end) return 0;
    if (r[start][end] != INT_MAX) return r[start][end];

    for (int k = start; k < end; k++) {
        int cost = min_cost(start, k) + min_cost(k, end);
        if (cost < r[start][end]) {
            r[start][end] = cost;
        }
    }
    return r[start][end];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            scanf("%d", &r[i][j]);
            r[j][i] = INT_MAX; // Initialize the other half of the matrix to INT_MAX
        }
    }

    // Initialize the diagonal to 0
    for (int i = 1; i <= n; i++) {
        r[i][i] = 0;
    }

    int result = min_cost(1, n);
    printf("%d\n", result);
    return 0;
}