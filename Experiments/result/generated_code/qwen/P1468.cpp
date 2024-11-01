#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_C 10000

int n, c;
int on[MAX_N + 1], off[MAX_N + 1];
int possible_states[MAX_C + 1][MAX_N];

void toggle(int *state) {
    for (int i = 1; i <= n; i++) {
        state[i] = !state[i];
    }
}

void toggle_odd(int *state) {
    for (int i = 1; i <= n; i += 2) {
        state[i] = !state[i];
    }
}

void toggle_even(int *state) {
    for (int i = 2; i <= n; i += 2) {
        state[i] = !state[i];
    }
}

void toggle_3k1(int *state) {
    for (int i = 1; i <= n; i += 3) {
        state[i] = !state[i];
    }
}

void dfs(int depth, int count, int *current_state) {
    if (count > c) return;
    if (depth == 5) {
        if (count == c) {
            int is_possible = 1;
            for (int i = 1; i <= n; i++) {
                if ((on[i] != -1 && current_state[i] != 1) || (off[i] != -1 && current_state[i] != 0)) {
                    is_possible = 0;
                    break;
                }
            }
            if (is_possible) {
                for (int i = 1; i <= n; i++) {
                    possible_states[count][i - 1] = current_state[i];
                }
            }
        }
        return;
    }

    int temp_state[MAX_N + 1];
    for (int i = 1; i <= n; i++) {
        temp_state[i] = current_state[i];
    }
    dfs(depth + 1, count + 1, temp_state);
    toggle(temp_state);
    dfs(depth + 1, count + 1, temp_state);
    toggle_odd(temp_state);
    dfs(depth + 1, count + 1, temp_state);
    toggle_even(temp_state);
    dfs(depth + 1, count + 1, temp_state);
    toggle_3k1(temp_state);
    dfs(depth + 1, count + 1, temp_state);
}

int main() {
    scanf("%d %d", &n, &c);

    int index = 0;
    while (scanf("%d", &on[index]) != EOF && on[index] != -1) {
        index++;
    }
    on[index] = -1;

    index = 0;
    while (scanf("%d", &off[index]) != EOF && off[index] != -1) {
        index++;
    }
    off[index] = -1;

    int initial_state[MAX_N + 1];
    for (int i = 1; i <= n; i++) {
        initial_state[i] = 1;
    }

    dfs(0, 0, initial_state);

    int result_count = 0;
    for (int i = 0; i <= c; i++) {
        int unique = 1;
        for (int j = 0; j < result_count; j++) {
            int same = 1;
            for (int k = 0; k < n; k++) {
                if (possible_states[i][k] != possible_states[j][k]) {
                    same = 0;
                    break;
                }
            }
            if (same) {
                unique = 0;
                break;
            }
        }
        if (unique) {
            printf("0");
            for (int k = 0; k < n; k++) {
                printf("%d", possible_states[i][k]);
            }
            printf("\n");
            result_count++;
        }
    }

    if (result_count == 0) {
        printf("IMPOSSIBLE\n");
    }

    return 0;
}