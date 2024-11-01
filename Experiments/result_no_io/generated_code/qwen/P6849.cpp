#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 100

int N, M;
int volumes[MAX_N];
int capacities[MAX_M];
int powers[MAX_N][MAX_M];

int dp[MAX_N + 1][MAX_M + 1];
int prev[MAX_N + 1][MAX_M + 1];

void knapsack() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (volumes[i - 1] <= j) {
                if (powers[i - 1][j - 1] + dp[i - 1][j - volumes[i - 1]] > dp[i - 1][j]) {
                    dp[i][j] = powers[i - 1][j - 1] + dp[i - 1][j - volumes[i - 1]];
                    prev[i][j] = j - volumes[i - 1];
                } else {
                    dp[i][j] = dp[i - 1][j];
                    prev[i][j] = j;
                }
            } else {
                dp[i][j] = dp[i - 1][j];
                prev[i][j] = j;
            }
        }
    }
}

void trace_back(int *result) {
    int j = M;
    for (int i = N; i >= 1; i--) {
        result[i - 1] = prev[i][j];
        if (prev[i][j] != j) {
            j -= volumes[i - 1];
        }
    }
}

int main() {
    FILE *in = fopen("drawer1.in", "r");
    FILE *out = fopen("drawer1.out", "w");

    fscanf(in, "%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        fscanf(in, "%d", &volumes[i]);
    }
    for (int i = 0; i < M; i++) {
        fscanf(in, "%d", &capacities[i]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fscanf(in, "%d", &powers[i][j]);
        }
    }

    knapsack();
    int result[N];
    trace_back(result);

    for (int i = 0; i < N; i++) {
        fprintf(out, "%d\n", result[i]);
    }

    fclose(in);
    fclose(out);

    return 0;
}