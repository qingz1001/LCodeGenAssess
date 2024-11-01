#include <stdio.h>
#include <stdbool.h>

#define MAX_V 25
#define MAX_G 15

int v, g;
int required[MAX_V];
int feeds[MAX_G][MAX_V];
int best_count = MAX_G + 1;
int best_solution[MAX_G];
int current_solution[MAX_G];

void dfs(int index, int count, int current[MAX_V]) {
    if (count >= best_count) return;

    bool satisfied = true;
    for (int i = 0; i < v; i++) {
        if (current[i] < required[i]) {
            satisfied = false;
            break;
        }
    }

    if (satisfied) {
        best_count = count;
        for (int i = 0; i < count; i++) {
            best_solution[i] = current_solution[i];
        }
        return;
    }

    if (index == g) return;

    // Don't use this feed
    dfs(index + 1, count, current);

    // Use this feed
    for (int i = 0; i < v; i++) {
        current[i] += feeds[index][i];
    }
    current_solution[count] = index + 1;
    dfs(index + 1, count + 1, current);
    for (int i = 0; i < v; i++) {
        current[i] -= feeds[index][i];
    }
}

int main() {
    scanf("%d", &v);
    for (int i = 0; i < v; i++) {
        scanf("%d", &required[i]);
    }

    scanf("%d", &g);
    for (int i = 0; i < g; i++) {
        for (int j = 0; j < v; j++) {
            scanf("%d", &feeds[i][j]);
        }
    }

    int current[MAX_V] = {0};
    dfs(0, 0, current);

    printf("%d", best_count);
    for (int i = 0; i < best_count; i++) {
        printf(" %d", best_solution[i]);
    }
    printf("\n");

    return 0;
}