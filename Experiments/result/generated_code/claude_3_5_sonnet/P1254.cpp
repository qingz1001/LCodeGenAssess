#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 8
#define MAX_SUM 256

int n;
int sectors[MAX_N];
int max_i;
int solutions[MAX_SUM][MAX_N];
int solution_count;

int check_sequence(int *arr, int size) {
    int sum[MAX_SUM] = {0};
    for (int mask = 1; mask < (1 << size); mask++) {
        int s = 0;
        for (int i = 0; i < size; i++) {
            if (mask & (1 << i)) {
                s += arr[i];
            }
        }
        if (s >= MAX_SUM) return 0;
        sum[s] = 1;
    }
    int i;
    for (i = 1; i < MAX_SUM && sum[i]; i++);
    return i - 1;
}

void dfs(int pos, int sum) {
    if (pos == n) {
        int i = check_sequence(sectors, n);
        if (i > max_i) {
            max_i = i;
            solution_count = 0;
        }
        if (i == max_i) {
            memcpy(solutions[solution_count++], sectors, n * sizeof(int));
        }
        return;
    }
    for (int i = 1; i <= MAX_SUM - sum; i++) {
        sectors[pos] = i;
        dfs(pos + 1, sum + i);
    }
}

int compare(const void *a, const void *b) {
    return memcmp(a, b, n * sizeof(int));
}

int main() {
    scanf("%d", &n);
    dfs(0, 0);
    printf("%d\n", max_i);
    qsort(solutions, solution_count, n * sizeof(int), compare);
    for (int i = 0; i < solution_count; i++) {
        if (i > 0 && memcmp(solutions[i], solutions[i-1], n * sizeof(int)) == 0) continue;
        for (int j = 0; j < n; j++) {
            printf("%d ", solutions[i][j]);
        }
        printf("\n");
    }
    return 0;
}