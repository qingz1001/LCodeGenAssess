#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 8
#define MAX_SUM 256

int n;
int sectors[MAX_N];
bool used[MAX_SUM + 1];
int max_i = 0;
int solutions[MAX_SUM][MAX_N];
int solution_count = 0;

void check_solution() {
    memset(used, 0, sizeof(used));
    int i;
    for (i = 1; i <= MAX_SUM; i++) {
        for (int len = 1; len <= n; len++) {
            int sum = 0;
            for (int j = 0; j < len; j++) {
                sum += sectors[(j + n) % n];
            }
            if (sum == i) {
                used[i] = true;
                break;
            }
        }
        if (!used[i]) break;
    }
    i--;
    
    if (i > max_i) {
        max_i = i;
        solution_count = 0;
    }
    
    if (i == max_i) {
        memcpy(solutions[solution_count], sectors, sizeof(sectors));
        solution_count++;
    }
}

void dfs(int idx) {
    if (idx == n) {
        check_solution();
        return;
    }
    
    for (int i = 1; i <= MAX_SUM; i++) {
        sectors[idx] = i;
        dfs(idx + 1);
    }
}

int main() {
    scanf("%d", &n);
    
    dfs(0);
    
    printf("%d\n", max_i);
    for (int i = 0; i < solution_count; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", solutions[i][j]);
            if (j < n - 1) printf(" ");
        }
        printf("\n");
    }
    
    return 0;
}