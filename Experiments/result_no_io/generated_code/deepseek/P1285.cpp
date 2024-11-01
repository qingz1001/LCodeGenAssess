#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100

int n;
bool graph[MAXN][MAXN];
bool visited[MAXN];
int group[MAXN];

bool dfs(int node, int g) {
    visited[node] = true;
    group[node] = g;
    for (int i = 0; i < n; i++) {
        if (graph[node][i]) {
            if (!visited[i]) {
                if (!dfs(i, 1 - g)) return false;
            } else if (group[i] == g) {
                return false;
            }
        }
    }
    return true;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int j;
        while (scanf("%d", &j) && j != 0) {
            graph[i][j - 1] = true;
        }
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (!dfs(i, 0)) {
                printf("No solution\n");
                return 0;
            }
        }
    }

    int group1[MAXN], group2[MAXN];
    int count1 = 0, count2 = 0;
    for (int i = 0; i < n; i++) {
        if (group[i] == 0) {
            group1[count1++] = i + 1;
        } else {
            group2[count2++] = i + 1;
        }
    }

    qsort(group1, count1, sizeof(int), compare);
    qsort(group2, count2, sizeof(int), compare);

    printf("%d", count1);
    for (int i = 0; i < count1; i++) {
        printf(" %d", group1[i]);
    }
    printf("\n");

    printf("%d", count2);
    for (int i = 0; i < count2; i++) {
        printf(" %d", group2[i]);
    }
    printf("\n");

    return 0;
}