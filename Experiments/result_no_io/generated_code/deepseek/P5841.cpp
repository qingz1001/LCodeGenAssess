#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 40000
#define MAXQ 100000
#define MAXL 10000

typedef struct {
    char str[MAXL + 1];
    int idx;
} String;

typedef struct {
    int x, y, idx;
} Task;

int n, q;
String strings[MAXN];
Task tasks[MAXQ];
int lcp[MAXN][MAXN];
int dp[MAXN];
int prev[MAXN];
int task_reward[MAXQ];
int task_order[MAXQ];
int task_count;

int cmp_strings(const void *a, const void *b) {
    return strcmp(((String *)a)->str, ((String *)b)->str);
}

int cmp_tasks(const void *a, const void *b) {
    return ((Task *)a)->x - ((Task *)b)->x;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%s", strings[i].str);
        strings[i].idx = i + 1;
    }
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &tasks[i].x, &tasks[i].y);
        tasks[i].x--;
        tasks[i].y--;
        tasks[i].idx = i + 1;
    }

    // Sort strings lexicographically
    qsort(strings, n, sizeof(String), cmp_strings);

    // Calculate lcp values
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int k = 0;
            while (strings[i].str[k] && strings[j].str[k] && strings[i].str[k] == strings[j].str[k]) {
                k++;
            }
            lcp[i][j] = k;
            lcp[j][i] = k;
        }
    }

    // Sort tasks by x
    qsort(tasks, q, sizeof(Task), cmp_tasks);

    // Dynamic programming to find the maximum value
    for (int i = 0; i < n; i++) {
        dp[i] = lcp[i][i + 1] * lcp[i][i + 1];
        prev[i] = -1;
        for (int j = 0; j < i; j++) {
            int new_value = dp[j] + lcp[j][i] * lcp[j][i];
            if (new_value > dp[i]) {
                dp[i] = new_value;
                prev[i] = j;
            }
        }
    }

    // Find the maximum value and the corresponding permutation
    int max_value = 0;
    int max_idx = -1;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max_value) {
            max_value = dp[i];
            max_idx = i;
        }
    }

    // Output the maximum value
    printf("%d\n", max_value);

    // Reconstruct the permutation
    int permutation[MAXN];
    int idx = max_idx;
    int perm_idx = 0;
    while (idx != -1) {
        permutation[perm_idx++] = strings[idx].idx;
        idx = prev[idx];
    }

    // Output the permutation
    for (int i = 0; i < n; i++) {
        printf("%d ", permutation[i]);
    }
    printf("\n");

    // Process tasks and calculate rewards
    for (int i = 0; i < q; i++) {
        int x = tasks[i].x;
        int y = tasks[i].y;
        if (prev[y] == x) {
            task_reward[i] = 1 << (tasks[i].idx - 1);
            task_order[task_count++] = tasks[i].idx;
        }
    }

    // Output the task rewards
    printf("%d", task_count);
    for (int i = 0; i < task_count; i++) {
        printf(" %d", task_order[i]);
    }
    printf("\n");

    return 0;
}