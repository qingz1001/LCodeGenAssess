#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 16
#define MAX_OP 100

char input[MAX_N];
char output[MAX_N];
int n;
char stack[3][MAX_N];
int top[3] = {0};
char op[MAX_OP][4];
int op_count = 0;

bool dfs(int depth) {
    if (depth == n) return true;
    
    for (int i = 0; i < 3; i++) {
        if (top[i] > 0 && stack[i][top[i] - 1] == output[depth]) {
            char train = stack[i][--top[i]];
            sprintf(op[op_count++], "%c,%c,D", train, 'A' + i);
            if (dfs(depth + 1)) return true;
            top[i]++;
            op_count--;
        }
    }
    
    if (input[depth] == output[depth]) {
        sprintf(op[op_count++], "%c,A,D", input[depth]);
        if (dfs(depth + 1)) return true;
        op_count--;
    } else {
        for (int i = 0; i < 2; i++) {
            stack[i][top[i]++] = input[depth];
            sprintf(op[op_count++], "%c,A,%c", input[depth], 'B' + i);
            if (dfs(depth)) return true;
            top[i]--;
            op_count--;
        }
    }
    
    return false;
}

int main() {
    scanf("%d %s", &n, input);
    scanf("%s", output);
    
    if (dfs(0)) {
        for (int i = 0; i < op_count; i++) {
            printf("%s\n", op[i]);
        }
    } else {
        printf("NO\n");
    }
    
    return 0;
}