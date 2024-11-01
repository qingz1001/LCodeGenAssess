#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 101

int n, c;
int on[MAX_N], off[MAX_N];
char state[MAX_N];
char result[1 << 16][MAX_N];
int result_count = 0;

void apply_button(int button) {
    for (int i = 1; i <= n; i++) {
        if (button == 1 ||
            (button == 2 && i % 2 == 1) ||
            (button == 3 && i % 2 == 0) ||
            (button == 4 && i % 3 == 1)) {
            state[i] = '0' + ('1' - state[i]);
        }
    }
}

void dfs(int depth, int button) {
    if (depth == c) {
        for (int i = 0; on[i] != -1; i++) {
            if (state[on[i]] != '1') return;
        }
        for (int i = 0; off[i] != -1; i++) {
            if (state[off[i]] != '0') return;
        }
        strcpy(result[result_count++], state + 1);
        return;
    }
    
    for (int i = button; i <= 4; i++) {
        apply_button(i);
        dfs(depth + 1, i);
        apply_button(i);
    }
}

int compare(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

int main() {
    scanf("%d %d", &n, &c);
    
    int i = 0;
    while (1) {
        scanf("%d", &on[i]);
        if (on[i] == -1) break;
        i++;
    }
    
    i = 0;
    while (1) {
        scanf("%d", &off[i]);
        if (off[i] == -1) break;
        i++;
    }
    
    memset(state, '1', sizeof(state));
    state[n + 1] = '\0';
    
    if (c > 4) c = c % 2 ? 3 : 4;
    
    dfs(0, 1);
    
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