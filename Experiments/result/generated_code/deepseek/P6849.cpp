#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define MAXM 100

int N, M;
int a[MAXN], b[MAXM];
int w[MAXN][MAXM];
int result[MAXN];

int main() {
    FILE *input = fopen("drawer1.in", "r");
    FILE *output = fopen("drawer1.out", "w");

    fscanf(input, "%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        fscanf(input, "%d", &a[i]);
    }
    for (int j = 0; j < M; j++) {
        fscanf(input, "%d", &b[j]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fscanf(input, "%d", &w[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        int max_power = -1;
        int best_drawer = 0;
        for (int j = 0; j < M; j++) {
            if (a[i] <= b[j] && w[i][j] > max_power) {
                max_power = w[i][j];
                best_drawer = j + 1;
            }
        }
        if (max_power != -1) {
            b[best_drawer - 1] -= a[i];
        }
        result[i] = best_drawer;
    }

    for (int i = 0; i < N; i++) {
        fprintf(output, "%d\n", result[i]);
    }

    fclose(input);
    fclose(output);
    return 0;
}