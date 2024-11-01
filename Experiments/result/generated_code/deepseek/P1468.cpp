#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100

int n, c;
int on[MAX_N + 1], off[MAX_N + 1];
int on_count, off_count;
char result[MAX_N + 1][MAX_N + 1];
int result_count = 0;

void apply_button(char *state, int button) {
    for (int i = 1; i <= n; i++) {
        if (button == 1) {
            state[i] = (state[i] == '1') ? '0' : '1';
        } else if (button == 2) {
            if (i % 2 == 1) state[i] = (state[i] == '1') ? '0' : '1';
        } else if (button == 3) {
            if (i % 2 == 0) state[i] = (state[i] == '1') ? '0' : '1';
        } else if (button == 4) {
            if (i % 3 == 1) state[i] = (state[i] == '1') ? '0' : '1';
        }
    }
}

int is_valid(char *state) {
    for (int i = 0; i < on_count; i++) {
        if (state[on[i]] != '1') return 0;
    }
    for (int i = 0; i < off_count; i++) {
        if (state[off[i]] != '0') return 0;
    }
    return 1;
}

void generate_states(int depth, char *state) {
    if (depth == c || depth == 4) {
        if (is_valid(state)) {
            strcpy(result[result_count], state + 1);
            result_count++;
        }
        return;
    }
    for (int i = 1; i <= 4; i++) {
        char new_state[MAX_N + 1];
        strcpy(new_state, state);
        apply_button(new_state, i);
        generate_states(depth + 1, new_state);
    }
}

int compare(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main() {
    scanf("%d %d", &n, &c);
    
    int temp;
    on_count = 0;
    while (1) {
        scanf("%d", &temp);
        if (temp == -1) break;
        on[on_count++] = temp;
    }
    
    off_count = 0;
    while (1) {
        scanf("%d", &temp);
        if (temp == -1) break;
        off[off_count++] = temp;
    }
    
    char initial_state[MAX_N + 1];
    for (int i = 1; i <= n; i++) {
        initial_state[i] = '1';
    }
    initial_state[n + 1] = '\0';
    
    generate_states(0, initial_state);
    
    qsort(result, result_count, sizeof(result[0]), compare);
    
    if (result_count == 0) {
        printf("IMPOSSIBLE\n");
    } else {
        for (int i = 0; i < result_count; i++) {
            printf("%s\n", result[i]);
        }
    }
    
    return 0;
}