#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000
#define MAXB 20

int N, B;
int preferences[MAXN][MAXB];
int capacities[MAXB];
int assignment[MAXN];
int used[MAXB];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int cow, int min_rank, int max_rank) {
    if (cow == N) {
        return max_rank - min_rank + 1;
    }

    int result = INT_MAX;
    for (int i = 0; i < B; i++) {
        int barn = preferences[cow][i] - 1;
        if (used[barn] < capacities[barn]) {
            used[barn]++;
            result = min(result, dfs(cow + 1, min(min_rank, i), max(max_rank, i)));
            used[barn]--;
        }
    }

    return result;
}

int main() {
    scanf("%d %d", &N, &B);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < B; j++) {
            scanf("%d", &preferences[i][j]);
        }
    }

    for (int i = 0; i < B; i++) {
        scanf("%d", &capacities[i]);
    }

    int result = dfs(0, INT_MAX, INT_MIN);
    printf("%d\n", result);

    return 0;
}