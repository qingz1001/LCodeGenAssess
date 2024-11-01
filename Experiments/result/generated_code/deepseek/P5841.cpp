#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 40000
#define MAXQ 100000
#define MAXL 10000

typedef struct {
    int x, y;
} Task;

int n, q;
char strings[MAXN][MAXL + 1];
Task tasks[MAXQ];

int lcp(char *s1, char *s2) {
    int len = 0;
    while (s1[len] && s2[len] && s1[len] == s2[len]) len++;
    return len;
}

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%s", strings[i]);
    }
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &tasks[i].x, &tasks[i].y);
        tasks[i].x--;
        tasks[i].y--;
    }

    // Sort strings to maximize lcp
    char *sorted_strings[MAXN];
    for (int i = 0; i < n; i++) {
        sorted_strings[i] = strings[i];
    }
    qsort(sorted_strings, n, sizeof(char *), compare_strings);

    // Calculate W(P^*_G)
    int max_value = 0;
    for (int i = 1; i < n; i++) {
        max_value += lcp(sorted_strings[i - 1], sorted_strings[i]) * lcp(sorted_strings[i - 1], sorted_strings[i]);
    }
    printf("%d\n", max_value);

    // Calculate P^*_B
    int task_count = 0;
    int task_indices[MAXQ];
    for (int i = 0; i < q; i++) {
        int x = tasks[i].x;
        int y = tasks[i].y;
        if (strcmp(strings[x], strings[y]) < 0) {
            task_indices[task_count++] = i + 1;
        }
    }
    printf("%d", task_count);
    for (int i = 0; i < task_count; i++) {
        printf(" %d", task_indices[i]);
    }
    printf("\n");

    // Output the sorted permutation
    int permutation[MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (strcmp(sorted_strings[i], strings[j]) == 0) {
                permutation[i] = j + 1;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", permutation[i]);
    }
    printf("\n");

    return 0;
}