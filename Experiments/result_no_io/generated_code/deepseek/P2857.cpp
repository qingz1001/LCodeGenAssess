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

int canAssign(int start, int end) {
    int i, j;
    for (i = 0; i < B; i++) {
        used[i] = 0;
    }
    for (i = 0; i < N; i++) {
        for (j = start; j <= end; j++) {
            int barn = preferences[i][j];
            if (used[barn] < capacities[barn]) {
                used[barn]++;
                break;
            }
        }
        if (j > end) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int i, j;
    scanf("%d %d", &N, &B);
    for (i = 0; i < N; i++) {
        for (j = 0; j < B; j++) {
            scanf("%d", &preferences[i][j]);
            preferences[i][j]--; // Convert to 0-based index
        }
    }
    for (i = 0; i < B; i++) {
        scanf("%d", &capacities[i]);
    }

    int ans = B;
    for (i = 0; i < B; i++) {
        for (j = i; j < B; j++) {
            if (j - i + 1 >= ans) continue;
            if (canAssign(i, j)) {
                ans = j - i + 1;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}