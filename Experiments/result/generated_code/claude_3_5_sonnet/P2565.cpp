#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 201
#define MAXM 201

int n, m;
int a[MAXN];
int dice[MAXN][MAXM];
int used[MAXN*MAXM];

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int check() {
    for (int i = 0; i < n; i++) {
        int wins = 0;
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                if (dice[i][j] > dice[a[i]][k]) wins++;
            }
        }
        if (wins <= m * m / 2) return 0;
    }
    return 1;
}

int dfs(int cur) {
    if (cur == n * m) return check();
    
    for (int i = 1; i <= n * m; i++) {
        if (used[i]) continue;
        used[i] = 1;
        dice[cur / m][cur % m] = i;
        if (dfs(cur + 1)) return 1;
        used[i] = 0;
    }
    return 0;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i]--;
    }

    if (dfs(0)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", dice[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("0\n");
    }

    return 0;
}