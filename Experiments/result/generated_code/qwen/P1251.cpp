#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000
#define MAX_R 10000000
#define MAX_P 10000
#define MAX_M 10000
#define MAX_F 10000
#define MAX_N_ 10000
#define MAX_S 10000

typedef struct {
    int days;
    int cost;
} Wash;

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int N, i, j, r[MAX_N], p, m, f, n, s;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &r[i]);
    }
    scanf("%d %d %d %d %d", &p, &m, &f, &n, &s);

    // Initialize DP tables
    int buy[MAX_N + 1][MAX_R + 1];
    int fast[MAX_N + 1][MAX_R + 1];
    int slow[MAX_N + 1][MAX_R + 1];

    for (i = 0; i <= N; i++) {
        for (j = 0; j <= MAX_R; j++) {
            buy[i][j] = fast[i][j] = slow[i][j] = INT_MAX;
        }
    }

    buy[0][0] = 0;
    fast[0][0] = 0;
    slow[0][0] = 0;

    for (i = 1; i <= N; i++) {
        for (j = 0; j <= MAX_R; j++) {
            if (buy[i - 1][j] != INT_MAX) {
                buy[i][j] = min(buy[i][j], buy[i - 1][j] + p * (r[i - 1] - j));
                if (j >= r[i - 1]) {
                    fast[i][j] = min(fast[i][j], fast[i - 1][j] + f);
                } else {
                    fast[i][j] = min(fast[i][j], fast[i - 1][j] + f + p * (r[i - 1] - j));
                }
                if (j >= r[i - 1]) {
                    slow[i][j] = min(slow[i][j], slow[i - 1][j] + s);
                } else {
                    slow[i][j] = min(slow[i][j], slow[i - 1][j] + s + p * (r[i - 1] - j));
                }
            }
        }
    }

    printf("%d\n", min(min(buy[N][0], fast[N][0]), slow[N][0]));

    return 0;
}