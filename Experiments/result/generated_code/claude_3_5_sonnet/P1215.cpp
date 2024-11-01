#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 21

int a, b, c;
int possible[MAX_CAPACITY];
int visited[MAX_CAPACITY][MAX_CAPACITY][MAX_CAPACITY];

void pour(int x, int y, int state[3]) {
    int amount = (state[x] < (state[y] - state[y])) ? state[x] : (state[y] - state[y]);
    state[x] -= amount;
    state[y] += amount;
}

void dfs(int state[3]) {
    if (visited[state[0]][state[1]][state[2]]) return;
    visited[state[0]][state[1]][state[2]] = 1;
    
    if (state[0] == 0) possible[state[2]] = 1;
    
    int new_state[3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i != j) {
                memcpy(new_state, state, sizeof(new_state));
                pour(i, j, new_state);
                dfs(new_state);
            }
        }
    }
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d %d %d", &a, &b, &c);
    
    int initial_state[3] = {0, 0, c};
    dfs(initial_state);
    
    int result[MAX_CAPACITY], count = 0;
    for (int i = 0; i <= c; i++) {
        if (possible[i]) {
            result[count++] = i;
        }
    }
    
    qsort(result, count, sizeof(int), compare);
    
    for (int i = 0; i < count; i++) {
        printf("%d", result[i]);
        if (i < count - 1) printf(" ");
    }
    printf("\n");
    
    return 0;
}