#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 101

int n, c;
int on[MAX_N], off[MAX_N];
char result[MAX_N][MAX_N];
int result_count = 0;

void toggle_all(char *state) {
    for (int i = 1; i <= n; i++)
        state[i] = '0' + ('1' - state[i]);
}

void toggle_odd(char *state) {
    for (int i = 1; i <= n; i += 2)
        state[i] = '0' + ('1' - state[i]);
}

void toggle_even(char *state) {
    for (int i = 2; i <= n; i += 2)
        state[i] = '0' + ('1' - state[i]);
}

void toggle_3k1(char *state) {
    for (int i = 1; i <= n; i += 3)
        state[i] = '0' + ('1' - state[i]);
}

int is_valid(char *state) {
    for (int i = 1; on[i] != -1; i++)
        if (state[on[i]] != '1') return 0;
    for (int i = 1; off[i] != -1; i++)
        if (state[off[i]] != '0') return 0;
    return 1;
}

void add_result(char *state) {
    if (is_valid(state)) {
        strcpy(result[result_count++], state + 1);
    }
}

int compare(const void *a, const void *b) {
    return strcmp((char*)a, (char*)b);
}

void generate_states(int button, char *state) {
    if (button > 4) {
        add_result(state);
        return;
    }
    
    char new_state[MAX_N];
    strcpy(new_state, state);
    
    generate_states(button + 1, new_state);
    
    if (c > 0) {
        switch(button) {
            case 1: toggle_all(new_state); break;
            case 2: toggle_odd(new_state); break;
            case 3: toggle_even(new_state); break;
            case 4: toggle_3k1(new_state); break;
        }
        generate_states(button + 1, new_state);
    }
}

int main() {
    scanf("%d %d", &n, &c);
    
    int i = 1;
    while (1) {
        scanf("%d", &on[i]);
        if (on[i] == -1) break;
        i++;
    }
    
    i = 1;
    while (1) {
        scanf("%d", &off[i]);
        if (off[i] == -1) break;
        i++;
    }
    
    char initial_state[MAX_N];
    memset(initial_state, '1', sizeof(initial_state));
    initial_state[n+1] = '\0';
    
    generate_states(1, initial_state);
    
    if (result_count == 0) {
        printf("IMPOSSIBLE\n");
    } else {
        qsort(result, result_count, sizeof(result[0]), compare);
        for (int i = 0; i < result_count; i++) {
            if (i == 0 || strcmp(result[i], result[i-1]) != 0) {
                printf("%s\n", result[i]);
            }
        }
    }
    
    return 0;
}