#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50000

int n;
int wish[MAXN][2];
int pos[MAXN];
int target[MAXN];

int min_cost = INT_MAX;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void dfs(int depth, int cost) {
    if (cost >= min_cost) return;
    if (depth == n) {
        min_cost = cost;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (pos[i] != target[i]) {
            int temp_pos[MAXN];
            for (int j = 0; j < n; j++) temp_pos[j] = pos[j];

            int move_count = 0;
            int j = i;
            while (pos[j] != target[i]) {
                move_count++;
                int next = wish[pos[j]][0] == pos[(j + 1) % n] ? wish[pos[j]][1] : wish[pos[j]][0];
                swap(&pos[j], &pos[(j + 1) % n]);
                j = (j + 1) % n;
            }

            dfs(depth + 1, cost + move_count);

            for (int j = 0; j < n; j++) pos[j] = temp_pos[j];
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &wish[i][0], &wish[i][1]);
        wish[i][0]--;
        wish[i][1]--;
    }

    for (int i = 0; i < n; i++) {
        pos[i] = i;
        target[i] = i;
    }

    dfs(0, 0);

    if (min_cost == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", min_cost);
    }

    return 0;
}