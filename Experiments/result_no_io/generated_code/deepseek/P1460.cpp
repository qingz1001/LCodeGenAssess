#include <stdio.h>
#include <stdbool.h>

#define MAX_V 25
#define MAX_G 15

int v, g;
int required[MAX_V];
int feeds[MAX_G][MAX_V];
int best_solution[MAX_G];
int best_count = MAX_G + 1;

bool is_valid(int *current_solution, int count) {
    int vitamins[MAX_V] = {0};
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < v; j++) {
            vitamins[j] += feeds[current_solution[i]][j];
        }
    }
    for (int i = 0; i < v; i++) {
        if (vitamins[i] < required[i]) {
            return false;
        }
    }
    return true;
}

void dfs(int start, int *current_solution, int count) {
    if (count >= best_count) return;
    if (is_valid(current_solution, count)) {
        best_count = count;
        for (int i = 0; i < count; i++) {
            best_solution[i] = current_solution[i];
        }
        return;
    }
    for (int i = start; i < g; i++) {
        current_solution[count] = i;
        dfs(i + 1, current_solution, count + 1);
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

    int current_solution[MAX_G];
    dfs(0, current_solution, 0);

    printf("%d", best_count);
    for (int i = 0; i < best_count; i++) {
        printf(" %d", best_solution[i] + 1);
    }
    printf("\n");

    return 0;
}