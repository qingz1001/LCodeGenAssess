#include <stdio.h>
#include <stdbool.h>

#define MAXN 101

int n, m;
bool enemy[MAXN][MAXN];
int solution[MAXN];
int bestSolution[MAXN];
int bestCount = 0;

void backtrack(int pos, int count) {
    if (pos > n) {
        if (count > bestCount) {
            bestCount = count;
            for (int i = 1; i <= n; i++) {
                bestSolution[i] = solution[i];
            }
        }
        return;
    }

    if (!solution[pos]) {
        bool canAdd = true;
        for (int i = 1; i < pos; i++) {
            if (solution[i] && enemy[i][pos]) {
                canAdd = false;
                break;
            }
        }
        if (canAdd) {
            solution[pos] = 1;
            backtrack(pos + 1, count + 1);
            solution[pos] = 0;
        }
    }
    backtrack(pos + 1, count);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            enemy[i][j] = false;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        enemy[u][v] = true;
        enemy[v][u] = true;
    }

    for (int i = 1; i <= n; i++) {
        solution[i] = 0;
    }
    backtrack(1, 0);

    printf("%d\n", bestCount);
    for (int i = 1; i <= n; i++) {
        printf("%d ", bestSolution[i]);
    }
    printf("\n");

    return 0;
}