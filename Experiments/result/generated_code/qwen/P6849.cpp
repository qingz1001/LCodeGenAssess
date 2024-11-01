#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 100

int N, M;
int a[MAX_N];
int b[MAX_M];
int w[MAX_N][MAX_M];

void dfs(int i, int used[], int current[], int *max_power) {
    if (i == N) {
        int power = 0;
        for (int j = 0; j < N; j++) {
            if (current[j] != 0) {
                power += w[j][current[j] - 1];
            }
        }
        if (power >= *max_power) {
            *max_power = power;
        }
        return;
    }

    for (int j = 0; j <= M; j++) {
        if (j == 0 || used[j]) continue;

        if (j >= a[i]) {
            used[j] = 1;
            current[i] = j;
            dfs(i + 1, used, current, max_power);
            used[j] = 0;
        } else {
            dfs(i + 1, used, current, max_power);
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    for (int j = 0; j < M; j++) {
        scanf("%d", &b[j]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &w[i][j]);
        }
    }

    int max_power = 0;
    int used[MAX_M + 1] = {0};
    int current[N] = {0};

    dfs(0, used, current, &max_power);

    for (int i = 0; i < N; i++) {
        printf("%d\n", current[i]);
    }

    return 0;
}